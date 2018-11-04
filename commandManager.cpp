#include "commandManager.h"
#include "Parsing.cpp"
#include <iostream>
#include <vector>

using namespace std;

commandManager::commandManager() {
    cout << "Constructor Built" << endl;
}

bool commandManager::handleCommand(const string &command, vector<string> parameters) {
    cout << "This is the initial pass: " << command << endl;

    Parsing::IRC_message ircMessage(command);

    cout << "This is the COMMAND: " << ircMessage.command << endl;
    string command = ircMessage.command;

    return true;
}
bool commandManager::away() {
    cout << "Away() command called" << endl;
    return true;
}