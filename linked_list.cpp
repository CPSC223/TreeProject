#include "linked_list.hpp"
#include <iostream>
#include <string>
#include <vector>

using namespace std;


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
    Node* newNodePtr = new Node(newNode);
    
    if (Head == nullptr){
        Head = newNodePtr;
        Tail = newNodePtr;
    } else {  
        Tail->next = newNodePtr;  // Link current Tail to the new node
        newNodePtr->last = Tail;  // Link new node's 'last' to the current Tail
        Tail = newNodePtr;  // Update Tail to the new node
    }
    newNodePtr->next = nullptr; 
    
}

void streetList::deleteNode(string blockName){
    Node* currentNode = Head;
    
    while (currentNode != nullptr) {
        if (currentNode->blockName == blockName) {  // Find the block with the specified name
            if (currentNode == Head) {  // If the node to be deleted is the Head
                Head = currentNode->next;
                if (Head != nullptr) {
                    Head->last = nullptr;  // Update the previous pointer of the new Head
                }
            } else if (currentNode == Tail) {  // If the node to be deleted is the Tail
                Tail = currentNode->last;
                if (Tail != nullptr) {
                    Tail->next = nullptr;  // Update the next pointer of the new Tail
                }
            } else {  // If the node is somewhere in the middle
                currentNode->last->next = currentNode->next;
                currentNode->next->last = currentNode->last;
            }
            delete currentNode;  // Free the memory
            return;
        }
        currentNode = currentNode->next;  // Move to the next node
    }
    
    cout << "Block " << blockName << " not found!" << endl;
}

void streetList::insertNode(Node& newNode, int position) {
    Node* newNodePtr = new Node(newNode);
    if (position == 0) {  // Insert at the beginning
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
    } else {  // Insert the node at the specified position
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
    cout << "The block " << newNode.blockName << " has " << newNode.treeCount << " trees." << endl;
}

Node* streetList::searchNode(string blockName) const {
    Node* current = Head;

    while (current != nullptr) {
        if (current->blockName == blockName) {
            return current;
        }
        current = current->next;
    }

    cout << "Node not found.\n";
    return nullptr;
}