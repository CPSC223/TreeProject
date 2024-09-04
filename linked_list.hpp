#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP
#endif

#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Node {
    int treeCount;
    string blockName;
    Node* last;
    Node* next;
};

class streetLinkedList {
public:
    Node* Head;
    Node* Base;
    string streetName;


    //constructor
    streetLinkedList();
    //deconstructor
    ~streetLinkedList();

    streetLinkedList* CreateNewNode(string blockName, int treeCount);

private:



};