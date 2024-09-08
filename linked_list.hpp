#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP
#endif

#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Node {
    int treeCount;
    int blockNum;
    Node* last;
    Node* next;
};

class streetList {
public:
    Node* Head;
    Node* Tail;
    string streetName;

    streetList(string street);

    ~streetList();

    streetList* CreateNewNode(string blockName, int treeCount);
    void append(Node& newNode);
    void printList() const;
    void insertNode(Node& newNode, int position);
    void deleteNode(int blockNum);
    void printSize(Node& newNode);
    Node* searchNode(int blockNum) const;
    


};