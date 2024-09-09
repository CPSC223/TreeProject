#include "linked_list.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cctype>
#include <locale>

using namespace std;

std::string cleanInput(const std::string& input) {
    std::string result;
    for (char c : input) {
        // Remove carriage returns and any other undesired characters
        if (c != '\r') {
            result += c;
        }
    }
    return result;
}

std::string trim(const std::string& str) {
    // Create a copy of the string to modify
    std::string trimmed = str;

    // Remove leading whitespace
    trimmed.erase(trimmed.begin(), std::find_if(trimmed.begin(), trimmed.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));

    // Remove trailing whitespace
    trimmed.erase(std::find_if(trimmed.rbegin(), trimmed.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
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

    while (getline(file, line)) {
        line = cleanInput(line);  // Remove hidden characters like '\r'
        cout << "File stream state after getline: " << file.good() << " Line: [" << line << "]" << endl;

        if (line.empty()) {
            continue;  // Skip empty lines
        }

        cout << "Line length after clean: " << line.length() << " Content: [" << line << "]" << endl;

        istringstream dataToParse(line);
        string streetName, treePerBlock;

        getline(dataToParse, streetName, ',');
        streetName = trim(streetName);  // Remove leading/trailing whitespace
        cout << "Parsing street: [" << streetName << "]" << endl;

        streetList newStreetList(streetName);
        int blockNum = 1;

        while (getline(dataToParse, treePerBlock, ',')) {
            treePerBlock = trim(treePerBlock);
            cout << "Block " << blockNum << " has " << treePerBlock << " trees." << endl;

            Node* newNode = new Node(treePerBlock, blockNum);
            newStreetList.append(newNode);  // Append the node
            blockNum++;
        }

        streetLinkedLists.push_back(newStreetList);  // Add the streetList to the vector
        cout << "Finished parsing street: " << streetName << endl;
    }

    file.close();
    cout << "Finished reading file" << endl;
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
    for (int i = 0; i < streetLinkedLists.size(); i++) {
        if (streetLinkedLists[i].streetName == streetName) {
            cout << "Street Found: " << streetName << endl;
            return;
        }
    }
    cout << "Street not found!" << endl;
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

void streetList::append(Node* newNode) {
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

void streetList::insertNode(Node* newNode, int position) {
    if (position == 0) {
        newNode->next = Head;
        if (Head != nullptr) {
            Head->last = newNode;
        }
        Head = newNode;
        if (Tail == nullptr) {
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

    if (currentNode == nullptr) {
        append(newNode);
    } else {
        newNode->next = currentNode->next;
        newNode->last = currentNode;
        if (currentNode->next != nullptr) {
            currentNode->next->last = newNode;
        } else {
            Tail = newNode;
        }
        currentNode->next = newNode;
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
