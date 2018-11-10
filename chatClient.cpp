#include "chatClient.h"
#include "tcpUserSocket.h"
#include <iostream>
#include <errno.h>
#include <thread>
#include <string>

using namespace std;

vector<string> channels;
string listeningChannel;
int ready = 1;


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

int chatClient::getPort(){
    return chatClient::port;
}

void switchChannelListening(string message){
    bool channelExists = false;
    for(auto channel : channels){
        if(message.substr(1,message.length()) == channel){
            listeningChannel = channel;
            cout << "Now listening to channel: " + channel << endl;
            channelExists = true;
            break;
        }
    }
    if(!channelExists){
        cout << "You are not Joined to channel: " + message.substr(1,message.length()) << endl;
    }
}

void addNewChannel(string msg){
    string channel = "";
    for(int i = 8; i < msg.size(); i++){
        if(msg.at(i) == ':'){
            break;
        }
        else{
            channel += msg.at(i);
        }
                
    }
    listeningChannel = channel;
    channels.push_back(channel);
    cout << msg << endl;
    cout << "now listening to channel: " + channel << endl;
}

void getChannelMessage(string msg){
string channel = "";
    for(int i = 1; i < msg.size(); i++){
        if(msg.at(i) == '-'){
            break;
        }
        else{
            channel += msg.at(i);
        }
    }
    if(channel == listeningChannel){
        cout << msg << endl;
    }
}

bool responseParser(string msg){
    if(msg == "QUIT") {
        ready = 0;
        return false;
        
    }
    else if(msg.at(1) == '#' || msg.at(1) == '&'){
        getChannelMessage(msg);
        return true;
    }
    else if(msg.substr(0,8) == "success:"){
        addNewChannel(msg);
        return true;
    } 
    else {
        cout << msg << endl;
        return true;
    }
}

void receiveMessages(cs457::tcpUserSocket* tcpUserSocket) {
    ssize_t val;

    bool cont = true;
    while(cont) {
        string msg;
        tie(msg,val) = tcpUserSocket->recvString();
        cont = responseParser(msg);
    }

    tcpUserSocket->sendString("QUIT");
}
int main(int argc, char **argv){
    InputParser input(argc, argv);
    chatClient chatClient1;
    chatClient1.setCmdFields(input);
    const string &filename = input.getCmdOption("-f");
    cs457::tcpUserSocket *socket = new cs457::tcpUserSocket("127.0.0.1",chatClient1.getPort());
    //shared_ptr<cs457::tcpUserSocket> socket (new cs457::tcpUserSocket("127.0.0.1",2000));
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
        }
        else if(message.substr(0,6) == "SWITCH"){
            switchChannelListening(message.substr(6,message.length()));
        } 
        
        else {
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