#include <iostream>
#include <string>
#include <vector>
#include "linked_list.hpp"

using namespace std;

int main() {
    cout << "Starting program..." << endl;
    string fileName = "StreetsAndTrees.csv";
    vector<streetList> streetLinkedLists;
    parseFile(fileName, streetLinkedLists);
    cout << "Parsed " << streetLinkedLists.size() << " streets." << endl;
    
    if (streetLinkedLists.size() > 0) {
        streetLinkedLists[0].printList();
    }
    
    return 0;
}
