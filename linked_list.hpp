#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP
#endif

#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Node {
    vector<int> treeCount;
    Node* last;
    Node* next;
};

class streetLinkedList {
public:
    Node* Head;
    Node* Base;
private:

};