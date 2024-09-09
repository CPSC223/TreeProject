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
    Node() : treeCount(""), blockNum(0), last(nullptr), next(nullptr) {}
    Node(const string& count, int num, Node* prev = nullptr, Node* following = nullptr)
        : treeCount(count), blockNum(num), last(prev), next(following) {}
};

class streetList {
public:
    string streetName;
    Node* Head;
    Node* Tail;

    streetList(const string& name);
    ~streetList();

    streetList(const streetList& other);
    streetList& operator=(const streetList& other);

    void append(Node& newNode);
    void printList() const;
    void insertNode(Node& newNode, int position);
    void deleteNode(int blockNum);
    void printSize(Node* newNode);
    int findSize() const;
    void initializeFromLine(const string& line);
    Node* searchNode(int blockNum) const;
};

void parseFile(const string& fileName, vector<streetList>& streetLinkedLists);
void selectStreet(vector<streetList>& streetLinkedLists, string& streetName);
void navigateStreet(vector<streetList>& streetLinkedLists, string& streetName);
string cleanInput(const string& input);
string trim(const string& str);
