#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP
#endif

#include <iostream>
#include <string>
#include <vector>

using namespace std;


struct Node {
    string treeCount;
    int blockNum;
    Node* last;
    Node* next;
};

class streetList {
public:
    string streetName;
    Node* Head;
    Node* Tail;
    streetList(const string& name);

    ~streetList();

    streetList* CreateNewNode(string blockName, int treeCount);
    void append(const Node& newNode);
    void printList() const;
    void insertNode(Node& newNode, int position);
    void deleteNode(int blockNum);
    void printSize(Node& newNode);
    Node* searchNode(int blockNum) const;

};

void parseFile(const string& fileName, vector<streetList>& streetLinkedLists);
void selectStreet(vector<streetList>& streetLinkedLists, string& streetName);
void navigateStreet(vector<streetList>& streetLinkedLists, string& streetName);
