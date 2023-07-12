#include <iostream>
#include "Node.h"
#include "CircularList.h"

using namespace std;

Node::Node() {
    next = nullptr;
    prev = nullptr;
}

Node::Node(int v){
    key = v;
    next = nullptr;
    prev = nullptr;
}

Node::~Node() = default;

int& Node::getKey() {
    return key;
}

int& Node::setKey(int v) {
    key = v;
    return key;
}

Node& Node::getNext() {
    return *next;
}

Node& Node::setNext(Node* node) {
    next = node;
    return *next;
}

Node& Node::getPrev() {
    return *prev;
}

Node& Node::setPrev(Node* node) {
    prev = node;
    return *prev;
}

CircularList::CircularList() {
    sentinel = new Node(NULL);
    length = 0;
}

CircularList::~CircularList() = default;

Node& CircularList::getSentinel() {
    return *sentinel;
}

void CircularList::displayList() {
    if(length == 0)
        cout << "List only contains the sentinel";
    else{
        cout << "sentinel ";
        Node* temp = &sentinel->getNext();
        while(temp != sentinel){
            cout << temp->getKey() << " ";
            temp = &temp->getNext();
        }
    }
    cout << endl << "Length is " << length << endl;
}

void CircularList::insertAfterSentinel(int value) {
    if(length == 0){
        Node* node = new Node(value);
        sentinel->setNext(node);
        sentinel->setPrev(node);
        node->setNext(sentinel);
        node->setPrev(sentinel);
        length++;
    }
    else{
        Node* node = new Node(value);
        node->setNext(&sentinel->getNext());
        sentinel->getNext().setPrev(node);
        sentinel->setNext(node);
        node->setPrev(sentinel);
        length++;
    }
}

void CircularList::insertBeforeSentinel(int value) {
    if(length == 0){
        Node* node = new Node(value);
        sentinel->setNext(node);
        sentinel->setPrev(node);
        node->setNext(sentinel);
        node->setPrev(sentinel);
        length++;
    }
    else{
        Node* node = new Node(value);
        node->setPrev(&sentinel->getPrev());
        sentinel->getPrev().setNext(node);
        sentinel->setPrev(node);
        node->setNext(sentinel);
        length++;
    }
}

void CircularList::insertAtPosition(int value, int position) {
    if(position == 0){
        cout << "Can't insert here; Sentinel is always at position 0" << endl;
    }
    else {
        if(position > length){
            cout << "Given position is too large; Inserting after sentinel" << endl;
            insertAfterSentinel(value);
        }
        else{
            Node* temp = sentinel;
            for(int i = 1; i <= position; i++)
                temp = &temp->getNext();
            Node* node = new Node(value);
            node->setPrev(&temp->getPrev());
            temp->getPrev().setNext(node);
            temp->setPrev(node);
            node->setNext(temp);
            length++;
        }
    }
}

void CircularList::removeAfterSentinel() {
    if(length == 0){
        cout << "List only contains the sentinel";
    }
    else{
        sentinel->setNext(&sentinel->getNext().getNext());
        delete &sentinel->getNext().getPrev();
        sentinel->getNext().setPrev(sentinel);
        length--;
    }
}

void CircularList::removeBeforeSentinel() {
    if(length == 0){
        cout << "List only contains the sentinel";
    }
    else{
        sentinel->setPrev(&sentinel->getPrev().getPrev());
        delete &sentinel->getPrev().getNext();
        sentinel->getPrev().setNext(sentinel);
        length--;
    }
}

void CircularList::removeByKey(int value) {
    Node* temp;
    for(temp = &sentinel->getNext(); temp != sentinel; temp = &temp->getNext())
        if(temp->getKey() == value){
            temp->getPrev().setNext(&temp->getNext());
            temp->getNext().setPrev(&temp->getPrev());
            delete temp;
            length--;
            break;
        }
    if(temp == sentinel)
        cout << "No node with key " << value << " in list" << endl;
}

Node& CircularList::listNthElement(Node* startingNode, int n) {
    //even if n is greater than the length, since the list is circular, it will loop through it as many times as necessary
    Node* temp = startingNode;
    for(int i = 0; i < n; i++){
        temp = &temp->getNext();
        if(temp == sentinel)
            temp = &temp->getNext();
    }
    cout << "Node " << temp->getKey() << " sits " << n << " nodes after node " << startingNode->getKey() << endl;
    return *temp;
}

void CircularList::josephusProblem(Node* startingNode, int jumpSize) {
    if(length == 0)
        cout << "List only contains the sentinel";
    else{
        if(length == 1){
            if(startingNode == sentinel)
                cout << "Node " << startingNode->getNext().getKey() << " is the sole survivor";
            else
                cout << "Node " << startingNode->getKey() << " is the sole survivor";
        }
        else{
            Node* toBeKilled = &listNthElement(startingNode,jumpSize);
            Node* next = &toBeKilled->getNext();
            cout << "Node " << toBeKilled->getKey() << " will be killed; ";
            toBeKilled->getPrev().setNext(&toBeKilled->getNext());
            toBeKilled->getNext().setPrev(&toBeKilled->getPrev());
            delete toBeKilled;
            length--;
            cout << "Remaining list: ";
            displayList();
            cout << endl;
            josephusProblem(next, jumpSize);
        }
    }
}

int main() {
    //code to test
    CircularList list;

    list.insertAfterSentinel(3);
    list.insertBeforeSentinel(2);
    list.insertAfterSentinel(1);
    list.insertAtPosition(50,1);
    list.displayList();
    cout << endl;

    list.removeAfterSentinel();
    list.removeBeforeSentinel();
    list.removeByKey(1);
    list.displayList();
    cout << endl;

    list.insertBeforeSentinel(4);
    list.insertAfterSentinel(2);
    list.insertBeforeSentinel(6);
    list.insertAtPosition(5, 4);
    list.insertAtPosition(1, 7);
    list.displayList();
    cout << endl;

    list.josephusProblem(&list.getSentinel().getNext(), 3);
    return 0;
}
