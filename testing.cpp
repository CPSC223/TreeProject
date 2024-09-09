
#include "unitTest.hpp"

int main() {
    testAppend();
    testInsertNode();
    testDeleteNode();
    testSearchNode();
    testPrintList();
    testParseData();

    cout << "All tests passed successfully!" << endl;
    return 0;
}