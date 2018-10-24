#include "chatClient.h"
#include <iostream>

using namespace std;

chatClient::chatClient() {
    string hostname = "";
    string nickname = "";
    int port = 0;
    string confFile = "";
    string testFile = "";
    string logFile = "";
    string password = "";
}
void chatClient::setCmdFields(InputParser input) {
    if(input.cmdOptionExists("-h")) {
        chatClient::hostname = input.getCmdOption("-h");
    }
    if(input.cmdOptionExists("-u")) {
        chatClient::nickname = input.getCmdOption("-u");
    }
    if(input.cmdOptionExists("-p")) {
        chatClient::port = stoi(input.getCmdOption("-p"));
    }
    if(input.cmdOptionExists("-c")) {
        chatClient::confFile = input.getCmdOption("-c");
    }
    if(input.cmdOptionExists("-t")) {
        chatClient::testFile = input.getCmdOption("-t");
    }
    if(input.cmdOptionExists("-L")) {
        chatClient::logFile = input.getCmdOption("-L");
    }

}
int main(int argc, char **argv){
    InputParser input(argc, argv);
    chatClient chatClient1;
    chatClient1.setCmdFields(input);
    const string &filename = input.getCmdOption("-f");
    if (!filename.empty()){
        // Do interesting things ...
    }

    return 0;
}