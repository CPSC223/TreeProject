/*
Name: Group 13
Class: CPSC223, Fall 2024
Date: September 8, 2024
Programming Assignment: Project 1
Description: This is the function implementation file that
houses the definitions for all functions
*/

#include "linked_list.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <locale>

using namespace std;

string trim(const string& str) {
    // Create a copy of the string to modify
    string trimmed = str;

    // Remove leading whitespace
    trimmed.erase(trimmed.begin(), find_if(trimmed.begin(), trimmed.end(), [](unsigned char ch) {
        return !isspace(ch);
    }));

    // Remove trailing whitespace
    trimmed.erase(find_if(trimmed.rbegin(), trimmed.rend(), [](unsigned char ch) {
        return !isspace(ch);
    }).base(), trimmed.end());

    return trimmed;
}

void parseFile(const string& fileName, vector<streetList>& streetLinkedLists) {
    ifstream file(fileName);
    string line;

    if (!file.is_open()) {
        cout << "File " << fileName << " was unable to open" << endl;
        return;
    }

    while(getline(file,line))
    {
        istringstream dataToParse(line);
        string streetName, treePerBlock;

        getline(dataToParse, streetName, ',');
        streetName = trim(streetName);  // Remove leading/trailing whitespace

        streetList newStreetList(streetName);
        int blockNum = 1;
        while (getline(dataToParse, treePerBlock, ',')) {
            treePerBlock = trim(treePerBlock);
            Node newNode(treePerBlock, blockNum);
            newStreetList.append(newNode);  // Append the node
            blockNum++;
        }
        streetLinkedLists.push_back(newStreetList);  // Add the streetList to the vector
    }
    file.close();
    cout << "Finished reading file" << endl;
}

streetList::streetList(const streetList& other)
    : Head(nullptr), Tail(nullptr), streetName(other.streetName) {
    Node* current = other.Head;
    while (current != nullptr) {
        Node* newNode = new Node(*current);
        this->append(*newNode);
        current = current->next;
    }
}

// Copy Assignment Operator
streetList& streetList::operator=(const streetList& other) {
    if (this == &other) {
        return *this;
    }

    // Clear the existing list
    Node* current = Head;
    while (current != nullptr) {
        Node* nextNode = current->next;
        delete current;
        current = nextNode;
    }
    Head = nullptr;
    Tail = nullptr;

    // Copy the streetName attribute
    streetName = other.streetName;

    // Copy the list
    current = other.Head;
    while (current != nullptr) {
        Node* newNode = new Node(*current);
        this->append(*newNode);
        current = current->next;
    }
    
    return *this;
}

void selectStreet(vector<streetList>& streetLinkedLists, string& streetName) {
    string streetChoice;
    bool validChoice = false;

    vector<string> validStreets = {"Indiana", "Nora", "Augusta", "Mission", "Sinto", "Sharp"};

    cout << "Please Select A Street to View!" << endl;
    cout << "[Indiana] [Nora] [Augusta] [Mission] [Sinto] [Sharp]" << endl;

    while (!validChoice) {
        cin >> streetChoice;

        for (const string& street : validStreets) {
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
    // Search for the street by name
    int streetNum = -1;
    for (int i = 0; i < streetLinkedLists.size(); i++) {
        if (streetLinkedLists[i].streetName == streetName) {
            cout << "Street Found: " << streetName << endl;
            streetNum = i;
            break;
        }
    }
    
    // If street not found, return
    if (streetNum == -1) {
        cout << "Street not found." << endl;
        return;
    }

    streetList& selectedStreet = streetLinkedLists[streetNum];
    Node* currentBlock = selectedStreet.Head;
    int blockIndex = 1; // Start at the first block
    bool keepWalking = true;

    // Start the block navigation loop
    while (keepWalking) {
        cout << "You are on block " << blockIndex << " of " << selectedStreet.streetName << endl;
        cout << "Trees on this block: " << currentBlock->treeCount << endl;

        int direction = -1; // Reset direction
        
        // Offer options based on the block position
        if (currentBlock->last == nullptr && currentBlock->next == nullptr) {
            // Single block street
            cout << "No more blocks to navigate. Exiting..." << endl;
            break;
        }
        else if (currentBlock->last == nullptr) {
            // First block, only option is to move forward or exit
            cout << "Would you like to move forward (1) or exit (0)?" << endl;
            while (direction != 1 && direction != 0) {
                cin >> direction;
                if (direction != 1 && direction != 0) {
                    cout << "Please enter a valid option: Forward (1) or Exit (0)." << endl;
                }
            }
        } 
        else if (currentBlock->next == nullptr) {
            // Last block, only option is to move backward or exit
            cout << "Would you like to move backward (2) or exit (0)?" << endl;
            while (direction != 2 && direction != 0) {
                cin >> direction;
                if (direction != 2 && direction != 0) {
                    cout << "Please enter a valid option: Backward (2) or Exit (0)." << endl;
                }
            }
        }
        else {
            // Middle blocks, option to move forward, backward, or exit
            cout << "Would you like to move forward (1), backward (2), or exit (0)?" << endl;
            while (direction != 1 && direction != 2 && direction != 0) {
                cin >> direction;
                if (direction != 1 && direction != 2 && direction != 0) {
                    cout << "Please enter a valid option: Forward (1), Backward (2), or Exit (0)." << endl;
                }
            }
        }

        // Handle movement based on user input
        if (direction == 1 && currentBlock->next != nullptr) {
            currentBlock = currentBlock->next;
            blockIndex++;
        } 
        else if (direction == 2 && currentBlock->last != nullptr) {
            currentBlock = currentBlock->last;
            blockIndex--;
        } 
        else if (direction == 0) {
            keepWalking = false;
        }
    }

    cout << "You have exited the street." << endl;
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

void streetList::append(Node& nodeNew) {
    Node* newNode = new Node(nodeNew);
    if (Head == nullptr) {
        cout << "List is empty, adding the first node (Block " << newNode->blockNum << ")" << endl;
        Head = Tail = newNode;
    } else {
        cout << "Appending node for Block " << newNode->blockNum << " after Block " << Tail->blockNum << endl;
        Tail->next = newNode;  // Link current Tail to the new node
        newNode->last = Tail;  // Set the new node's last pointer to the current Tail
        Tail = newNode;        // Update the Tail to be the new node
    }
}

void streetList::printList() const {
    Node* currentNode = Head; 
    while (currentNode != nullptr) {
        cout << "Block " << currentNode->blockNum << " contains " << currentNode->treeCount << " trees!" << endl;
        currentNode = currentNode->next; 
    }
}

int streetList::findSize() const {
    int size = 0;
    Node* current = Head;
    while (current != nullptr) {
        size++;
        current = current->next;
    }
    return size;
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

void streetList::deleteNode(int blockNum) {
    Node* currentNode = Head;

    while (currentNode != nullptr) {
        if (currentNode->blockNum == blockNum) {
            if (currentNode == Head) {
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

void streetList::printSize(Node* newNode) {
    cout << "Block " << newNode->blockNum << " has " << newNode->treeCount << " trees." << endl;
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
