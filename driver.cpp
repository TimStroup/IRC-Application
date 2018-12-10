#include <iostream>
#include <string> 
#include <tuple> 
#include <thread> 
#include <vector> 
#include <memory> 
#include <fstream>
#include <istream>
#include <sstream>
#include "tcpUserSocket.h"
#include "tcpServerSocket.h"
#include "commandManager.h"
#include "User.h"
#include "channel.h"
#include "inputParser.cpp"



using namespace std;

bool ready = true; 
vector<User*> chatClientUsers;
vector<channel*> channels;
vector<string> additionalPorts;
string inputPort = "";
string configFile = "conf/chatserver.conf";
string dbFile = "db/";

int cclient(shared_ptr<cs457::tcpUserSocket> clientSocket, int id)
{
    //User Stuff
    string tempNick = "Guest" + to_string(id);
    User clientUser(tempNick, clientSocket);

    //Add this client to the Server's vector of clients
    chatClientUsers.push_back(&clientUser);

    ifstream helpFile(dbFile + "banner.txt");
    string line;
    while(getline(helpFile,line)){
        clientUser.socketConnection->sendString(line);
    }
    //Create Command Manager for this cclient to handle the incoming messages/commands
    commandManager commandManager1(&clientUser, &chatClientUsers, &channels, dbFile);
    
    //Variable Allocations
    string msg;
    ssize_t val;
    bool cont = true;

    //The main code of this server, reads in a message from the client and stores it as
    // a string called "msg". msg is then passed to the commandManager to process the message.
    // commandManager.handleCommand then returns a boolean on whether or not to continue the
    // while loop.  
    while (cont) 
    {
        tie(msg,val) = clientSocket.get()->recvString();
        
        // Adding a carriage return to help with the parameter parsing
        msg.push_back('\r');

        vector<string> testVector;
        cont = commandManager1.handleCommand(msg, testVector);

        cout << "[SERVER] CLIENT [" << clientUser.getNick() << "] sent message: " << msg << endl;
        //string s =  "[SERVER REPLY] You sent: " + msg  + "\n"; 
        //thread childT1(&cs457::tcpUserSocket::sendString,clientSocket.get(),s,true);
        //thread childT2(&cs457::tcpUserSocket::sendString,clientSocket.get(),msg,true);
        //thread childT3(&cs457::tcpUserSocket::sendString,clientSocket.get(),"\n",true);
        
        //childT1.join();
        //childT2.join(); 
        //childT3.join(); 
        //clientSocket.get()->sendString(msg); 
        //clientSocket.get()->sendString("\n"); 

    }

    //clientSocket.get()->sendString("goodbye"); 
    
    clientSocket.get()->closeSocket();
    cout << "I closed the socket" << endl;
    return 1; 
}


void parseConfigFile(){
    const char* file = configFile.c_str();
    ifstream fileInput(file,ifstream::in);
    string line;
   
    while(getline(fileInput,line)){
        string value;
        vector<string> configs;
        istringstream tokens(line);
        while(getline(tokens,value,' ')){
            configs.push_back(value);
        }
        if(configs.at(0) == "port"){
            inputPort = configs.at(1);            
        }
        else if(configs.at(0) == "dbpath"){
            dbFile = configs.at(1);
        }
        else if(configs.at(0) == "additional_ports"){
            string port;
            istringstream ports(configs.at(1));
            while(getline(ports,port,',')){
                additionalPorts.push_back(port);
            }
        }
    }
    
}

void setOptions(InputParser input){

    if(input.cmdOptionExists("-port")){
       inputPort = input.getCmdOption("-port");
    }
    if(input.cmdOptionExists("-configuration")){
        configFile = input.getCmdOption("-configuration");
    }
    if(input.cmdOptionExists("-db")){
        dbFile = input.getCmdOption("-db");
    }
}

void acceptConnections() {
    cout << "Initializing Socket" << std::endl; 
    cs457::tcpServerSocket mysocket(stoi(inputPort));
    cout << "Binding Socket" << std::endl; 
    mysocket.bindSocket();
    cout << "Waiting to Accept Socket on: " + inputPort << std::endl;
    mysocket.listenSocket();

    int id = 0;
    vector<unique_ptr<thread>> threadList;
    
    bool readyThread = true;

    while(readyThread) {
        shared_ptr<cs457::tcpUserSocket> clientSocket;
        int val;
        tie(clientSocket,val) = mysocket.acceptSocket();
        unique_ptr<thread> t = make_unique<thread>(cclient,clientSocket,id);
        threadList.push_back(std::move(t)); 
        id++;
    }

    for (auto& t : threadList) {
        t.get()->join();
    }
}

void persistantChannels(){
    const char* file = "db/channels.txt";
    ifstream fileInput(file,ifstream::in);
    string line;
   
    while(getline(fileInput,line)){
        channels.push_back(new channel("&" +line,""));
    }
}

int main(int argc, char * argv[])
{
    InputParser input(argc,argv);

    setOptions(input);
    parseConfigFile();
    persistantChannels();

    thread acceptThread(acceptConnections);
    
    while(true) {
        string message;
        getline(cin,message);
        cout << message << endl;
    }
    cout << "Server is shutting down after one client" << endl; 
    
    return 0; 
}