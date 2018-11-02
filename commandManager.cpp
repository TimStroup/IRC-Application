#include "commandManager.h"
#include "Parsing.cpp"
#include <iostream>
#include <vector>

using namespace std;

commandManager::commandManager() {
    
    cout << "Constructor Built" << endl;
}

bool commandManager::handleCommand(const string &command, vector<string> parameters) {
    cout << command << endl;
    return true;
}
bool commandManager::away() {
    cout << "Away() command called" << endl;
    return true;
}