#include "linked_list.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;


void parseFile(const string& fileName, vector<streetList>& streetLinkedLists) {
    cout << "HELLO" << endl;
    ifstream file(fileName);
    string line;
    cout << "1" << endl;
    if (!file.is_open()) {
        cerr << "File " << fileName << " was unable to open" << endl;
        return;
    }
    cout << "2" << endl;
while (getline(file, line)) {
    stringstream ss(line);
    string streetName, blockData;

    // Read street name
    getline(ss, streetName, ',');

    // Create new street list for the street name
    streetList newStreetList(streetName);
    int blockCounter = 1; // Move blockCounter initialization here

    // Process each block data
    while (getline(ss, blockData, ',')) {
        Node newNode;
        newNode.blockNum = blockCounter;
        newNode.treeCount = blockData; // Directly use blockData
        newNode.last = nullptr;
        newNode.next = nullptr;

        // Append node to the current street list
        newStreetList.append(newNode);
        blockCounter++;
    }

    // Add the street list to the vector
    streetLinkedLists.push_back(newStreetList);
}
    cout << "8" << endl;

    file.close();
    cout << "9" << endl;

}

void selectStreet(vector<streetList>& streetLinkedLists, string& streetName) {
    string streetChoice;
    bool validChoice = false;

    // List of valid streets
    vector<string> validStreets = {"Indiana", "Nora", "Augusta", "Mission", "Sinto", "Sharp"};

    cout << "Please Select A Street to View!" << endl;
    cout << "[Indiana] [Nora] [Augusta] [Mission] [Sinto] [Sharp]" << endl;

    while (!validChoice) {
        cin >> streetChoice;

        for (const string& street : validStreets) { //iterate through vector
            if (street == streetChoice) {
                validChoice = true; 
                break;
            }
        }

        if (!validChoice) {
            cout << "Invalid street name. Please try again: " << endl;
        }
    }
    streetName = streetChoice;
}

void navigateStreet(vector<streetList>& streetLinkedLists, string& streetName) {
    for (int i = 0; i < streetLinkedLists.size(); i++) {
        if (streetLinkedLists[i].streetName == streetName)
        {
            cout << "Street Found: " << streetName;
        }
    }
    cout << "oh no" << endl;
    
}

//LinkedList Functions


void streetList::printList() const {
    Node* currentNode = Head;
    while (currentNode != nullptr)
    {
        cout << "Block " << currentNode->blockNum << " contains " << currentNode->treeCount << " trees!" << endl;
        currentNode = currentNode ->next;
    }
}
streetList::streetList(const string& street) {
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

void streetList::append(const Node& newNode){
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