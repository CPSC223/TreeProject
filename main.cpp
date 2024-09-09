/*
Name: Group 14
Class: CPSC223, Fall 2024
Date: September 8, 2024
Programming Assignment: Project 1
Description: Main function!
*/
#include "linked_list.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>


using namespace std;

int main() {
    string streetName;
    string fileName = "StreetsAndTrees.csv";
    vector<streetList> streetLinkedLists;

    // Parse the file to load street data
    parseFile(fileName, streetLinkedLists);

    bool keepRunning = true;
    
    while (keepRunning) {
        string response;
        selectStreet(streetLinkedLists, streetName);
        navigateStreet(streetLinkedLists, streetName);

        cout << "Would you like to view another street? (yes/no)" << endl;
        cin >> response;

        // Convert response to lowercase for case-insensitive comparison
        transform(response.begin(), response.end(), response.begin(), ::tolower);

        if (response != "yes") {
            keepRunning = false;
        }
    }

    cout << "Goodbye!" << endl;
    return 0;
}