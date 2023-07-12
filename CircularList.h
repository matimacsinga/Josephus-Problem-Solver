#ifndef MAIN_CPP_CIRCULARLIST_H
#define MAIN_CPP_CIRCULARLIST_H
#include <iostream>

using namespace std;

class CircularList {
private:
    Node* sentinel;
    int length;
public:
    CircularList();
    ~CircularList();
    Node& getSentinel();
    void displayList();
    void insertAfterSentinel(int value);
    void insertBeforeSentinel(int value);
    void insertAtPosition(int value, int position);
    void removeAfterSentinel();
    void removeBeforeSentinel();
    void removeByKey(int value);
    Node& listNthElement(Node* startingNode, int n);
    void josephusProblem(Node* startingNode, int jumpSize);
};

#endif
