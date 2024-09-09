#include "unitTest.hpp"

void testAppend() {
    streetList list("Mission");
    Node node1("10",1);
    Node node2("20",2);

    list.append(node1);
    list.append(node2);
    if(list.findSize() == 2 && list.Head->treeCount == "10")
    {
        cout << "Test Append Passed Successfully" << endl;
    }
}

void testInsertNode() {
    streetList list("Sharp");

    Node node1("10", 1);
    Node node2("20", 2);
    Node node3("30", 3);

    list.append(node1);
    list.append(node2);
    list.insertNode(node3, 1);

    if(list.findSize() == 3 && list.Head->next->next->treeCount == "30")
    {
        cout << "Test Insert Node Passed Successfully" << endl;
    } else{
        cout << "AppendNode failed" << endl;

    }

}

void testDeleteNode() {
    streetList list("Sharp");

    Node node1("10", 1);
    Node node2("20", 2);

    list.append(node1);
    list.append(node2);

    list.deleteNode(1);
    if (list.findSize() != 1 || list.Head->blockNum != 2)
    {
        cout << "DeleteNode failed" << endl;
        return;
    }
    list.deleteNode(2);
    if (list.findSize() != 0)
    {
        cout << "DeleteNode failed" << endl;
        return;
    }
    cout << "testDeleteNode Passed Successfully" << endl;
}

void testSearchNode() {
    streetList list("Sharp");

    Node node1("10", 1);
    Node node2("20", 2);

    list.append(node1);
    list.append(node2);

    Node* result = list.searchNode(2);
    if (result == nullptr || result->blockNum != 2)
    {
        cout << "SearchNode failed" << endl;
        return;
    }

    result = list.searchNode(50);
    if (result != nullptr){
        cout << "testSearchNode passed successfully" << endl;
    }
}

void testPrintList() {
    streetList list("Sharp");

    Node node1("10", 1);
    Node node2("20", 2);

    list.append(node1);
    list.append(node2);

    list.printList();
    cout << "testPrintList passed successfully!" << endl;
}


void testParseData(){
    vector<streetList> vectorLists;
    parseFile("testData.csv", vectorLists);
}