#include <iostream>
#include <string> 
#include <tuple> 
#include <thread> 
#include <vector> 
#include <memory> 
#include "tcpUserSocket.h"
#include "tcpServerSocket.h"
#include "commandManager.h"
#include "User.h"
#include "channel.h"

using namespace std;

bool ready = true; 
vector<User*> chatClientUsers;
vector<channel*> channels;

int cclient(shared_ptr<cs457::tcpUserSocket> clientSocket, int id)
{
    //User Stuff
    string tempNick = "Guest" + to_string(id);
    User clientUser(tempNick, clientSocket);

    //Add this client to the Server's vector of clients
    chatClientUsers.push_back(&clientUser);

    //Create Command Manager for this cclient to handle the incoming messages/commands
    commandManager commandManager1(&clientUser, &chatClientUsers, &channels);
    
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
        string s =  "[SERVER REPLY] You sent: " + msg  + "\n"; 
        thread childT1(&cs457::tcpUserSocket::sendString,clientSocket.get(),s,true);
        //thread childT2(&cs457::tcpUserSocket::sendString,clientSocket.get(),msg,true);
        //thread childT3(&cs457::tcpUserSocket::sendString,clientSocket.get(),"\n",true);
        
        childT1.join();
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

int main(int argc, char * argv[])
{
    cout << "Initializing Socket" << std::endl; 
    cs457::tcpServerSocket mysocket(2000);
    cout << "Binding Socket" << std::endl; 
    mysocket.bindSocket(); 
    cout << "Listening Socket" << std::endl; 
    mysocket.listenSocket(); 
    cout << "Waiting to Accept Socket" << std::endl;
    int id = 0; 
    vector<unique_ptr<thread>> threadList; 
  
    while (ready)
    { 
        shared_ptr<cs457::tcpUserSocket> clientSocket;
        int val; 
        tie(clientSocket,val) = mysocket.acceptSocket();
        cout << "value for accept is " << val << std::endl; 
        cout << "Socket Accepted" << std::endl; 
        unique_ptr<thread> t = make_unique<thread>(cclient,clientSocket,id);
        threadList.push_back(std::move(t)); 
        id++; //not the best way to go about it. 
       // threadList.push_back(t); 
           
    }

    for (auto& t: threadList)
    {
        t.get()->join();
    }
    
    
    cout << "Server is shutting down after one client" << endl; 
    return 0; 
}