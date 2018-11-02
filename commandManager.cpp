#include "commandManager.h"
#include <iostream>

using namespace std;

commandManager::commandManager() {
    //Default Constructor, do nothing?
    cout << "Command Manager constructed" << endl;
}

bool commandManager::away() {
    cout << "Away() command called" << endl;
    return true;
}