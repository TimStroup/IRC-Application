#include "chatClient.h"
#include "tcpUserSocket.h"
#include <iostream>
#include <errno.h>
#include <thread>

using namespace std;

chatClient::chatClient(){
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
    cs457::tcpUserSocket *socket = new cs457::tcpUserSocket("127.0.0.1",2000);

    int ready = 1;
    cout << socket->connectToServer() << endl;
    char* message = new char[512];
    string recvMessage;
    ssize_t val;
    //thread readThread(socket);
    //thread writeThread(socket);
    while(ready == 1){
        cin.getline(message,512);
        socket->sendString(message,true);
        tie(recvMessage,val) = socket->recvString();
        if(recvMessage == "QUIT") {
            ready = 0;
        } else {
            cout << recvMessage << endl;
        }
    }
    
    if (!filename.empty()){
        // Do interesting things ...
    }
    
    delete socket;
    delete message;
    return 0;
}