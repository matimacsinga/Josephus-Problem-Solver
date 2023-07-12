#ifndef MAIN_CPP_NODE_H
#define MAIN_CPP_NODE_H

class Node {

private:
    int key;
    Node* next;
    Node* prev;

public:
    Node();
    explicit Node(int v);
    ~Node();
    int& getKey();
    int& setKey(int v);
    Node& getNext();
    Node& setNext(Node* node);
    Node& getPrev();
    Node& setPrev(Node* node);
};

#endif
