#include <iostream>
#include <string>
#include <vector>
#include "linked_list.cpp"

using namespace std;

int main() {
    string streetName = "hiN";
    string fileName = "StreetsAndTrees.csv";
    vector<streetList> streetLinkedLists;
    parseFile(fileName, streetLinkedLists);
    // selectStreet(streetLinkedLists, streetName);
    // navigateStreet(streetLinkedLists, streetName);
    cout << streetLinkedLists.size() << endl;
}