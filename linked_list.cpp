#include "linked_list.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;


void parseFile(const string& fileName, vector<streetList>& streetLinkedLists){
    ifstream file(fileName);
    string line, blockData;
    if(!file.is_open()) {
        cout << "File was unable to open" << endl;
        return;
    }

    while (getline(file, line)) {
        int blockCounter = 1;
        stringstream ss(line);

        string streetName;
        getline(ss, streetName, ',');

        streetList newStreetList(streetName);
        while(getline(ss,blockData, ',')){
            int treeCount = stoi(blockData);

            Node newNode;
            newNode.blockNum = blockCounter;
            newNode.treeCount = treeCount;
            newNode.last = nullptr;
            newNode.next = nullptr;

            // Append node to the current street list
            newStreetList.append(newNode);
            blockCounter++;
        }
        streetLinkedLists.push_back(newStreetList);
    }
    file.close();
    return;
}



//LinkedList Functions
streetList::streetList(string street) {
    Head = nullptr;
    Tail = nullptr;
    streetName = street;
}

streetList::~streetList() {
    Node* currentNode = Head;
    while (currentNode != nullptr) {
        Node* nextNode = currentNode->next;
        delete currentNode;
        currentNode = nextNode;
    }
}

void streetList::append(Node& newNode){
     Node* newNodePtr = new Node();  // Create a new empty node

    // Assign values from newNode
    newNodePtr->blockNum = newNode.blockNum;
    newNodePtr->treeCount = newNode.treeCount;
    newNodePtr->last = nullptr;
    newNodePtr->next = nullptr;

    if (Head == nullptr) {
        Head = newNodePtr;
        Tail = newNodePtr;
    } else {
        Tail->next = newNodePtr;
        newNodePtr->last = Tail;
        Tail = newNodePtr;
    }
}

void streetList::deleteNode(int blockNum){
    Node* currentNode = Head;
    
    while (currentNode != nullptr) {
        if (currentNode->blockNum == blockNum) {  // Find the block with the specified name
            if (currentNode == Head) {  // If the node to be deleted is the Head
                Head = currentNode->next;
                if (Head != nullptr) {
                    Head->last = nullptr; 
                }

            } else if (currentNode == Tail) {  
                Tail = currentNode->last;
                if (Tail != nullptr) {
                    Tail->next = nullptr;  
                }

            } else { 
                currentNode->last->next = currentNode->next;
                currentNode->next->last = currentNode->last;
            }
            delete currentNode;
            return;
        }
        currentNode = currentNode->next;  
    }
    
    cout << "Block " << blockNum << " not found" << endl;
}

void streetList::insertNode(Node& newNode, int position) {

    Node* newNodePtr = new Node();
    newNodePtr->blockNum = newNode.blockNum;
    newNodePtr->treeCount = newNode.treeCount;
    newNodePtr->next = nullptr;
    newNodePtr->last = nullptr;

    if (position == 0) {  
        newNodePtr->next = Head;
        if (Head != nullptr) {
            Head->last = newNodePtr;
        }
        Head = newNodePtr;
        if (Tail == nullptr) {  // If the list was empty, update the Tail
            Tail = Head;
        }
        return;
    }
    
    Node* currentNode = Head;
    int currentPosition = 0;
    
    while (currentNode != nullptr && currentPosition < position - 1) {
        currentNode = currentNode->next;
        currentPosition++;
    }
    
    if (currentNode == nullptr) {  // If position is out of bounds, append at the end
        append(*newNodePtr);
    } else { 
        newNodePtr->next = currentNode->next;
        newNodePtr->last = currentNode;
        
        if (currentNode->next != nullptr) {
            currentNode->next->last = newNodePtr;
        } else {  // If inserting at the end
            Tail = newNodePtr;
        }
        
        currentNode->next = newNodePtr;
    }
}

void streetList::printSize(Node& newNode) {
    cout << "Block " << newNode.blockNum << " has " << newNode.treeCount << " trees." << endl;
}

Node* streetList::searchNode(int blockNum) const {
    Node* current = Head;

    while (current != nullptr) {
        if (current->blockNum == blockNum) {
            return current;
        }
        current = current->next; 
    }

    cout << "Node not found.\n";
    return nullptr;
}