#include "chatClient.h"
#include "tcpUserSocket.h"
#include <iostream>
#include <errno.h>
#include <thread>
#include <string>

using namespace std;

string status = "";

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

void receiveMessages(cs457::tcpUserSocket* tcpUserSocket) {
    ssize_t val;

    while(status != "QUIT") {
        string msg;
        tie(msg,val) = tcpUserSocket->recvString();

        if(msg == "QUIT") {
            status = "QUIT";
        } else {
            cout << msg << endl;
        }
    }
}
int main(int argc, char **argv){
    InputParser input(argc, argv);
    chatClient chatClient1;
    chatClient1.setCmdFields(input);
    const string &filename = input.getCmdOption("-f");
    cs457::tcpUserSocket *socket = new cs457::tcpUserSocket("127.0.0.1",2000);
    //shared_ptr<cs457::tcpUserSocket> socket (new cs457::tcpUserSocket("127.0.0.1",2000));
    int ready = 1;
    cout << socket->connectToServer() << endl;
    
    string message;
    string recvMessage;
    ssize_t val;
    
    thread readThread(receiveMessages,socket);
    
    while(ready == 1){
        getline(cin, message);
        //string string(message);
        if(message == "QUIT") {
            ready = 0;
            socket->sendString(message,true);
        } else {
            socket->sendString(message,true);
        }
        //tie(recvMessage,val) = socket->recvString();
        //if(recvMessage == "QUIT") {
        //    ready = 0;
        //} else {
        //    cout << recvMessage << endl;
        //}
    }
    
    readThread.join();
    if (!filename.empty()){
        // Do interesting things ...
    }
    
    //delete socket;
    //delete message;
    return 0;
}