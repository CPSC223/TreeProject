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
        // Allow the user to select a street
        selectStreet(streetLinkedLists, streetName);

        // Check if the user typed "exit" in selectStreet
        if (streetName == "exit") {
            keepRunning = false;
            break;
        }

        // Navigate the selected street
        navigateStreet(streetLinkedLists, streetName);

        // After navigation, ask the user if they want to switch streets or quit
        string response;
        bool validResponse = false;
        
        while (!validResponse) {
            cout << "Would you like to view another street? (yes/no)" << endl;
            cin >> response;

            // Convert response to lowercase for case-insensitive comparison
            transform(response.begin(), response.end(), response.begin(), ::tolower);

            if (response == "yes") {
                validResponse = true;
            } else if (response == "no") {
                validResponse = true;
                keepRunning = false; // Exit the loop if they say "no"
            } else {
                cout << "Please enter a valid option: 'yes' or 'no'." << endl;
            }
        }
    }

    cout << "Goodbye!" << endl;
    return 0;
}