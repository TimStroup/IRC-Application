#include "tcpUserSocket.h"
#include <memory> 
#include <cstring> 
#include <mutex> 
#include <iostream>

using namespace std; 

cs457::tcpUserSocket::tcpUserSocket(const string srvrAddress, int port) 
{
    tcpUserSocket::userSocket = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    cout << userSocket << endl;
    memset(&(tcpUserSocket::serverAddress),'0',sizeof(tcpUserSocket::serverAddress));
    tcpUserSocket::serverAddress.sin_family = AF_INET;
    tcpUserSocket::serverAddress.sin_port = htons(port);

    cout << inet_pton(AF_INET,"127.0.0.1",&tcpUserSocket::serverAddress.sin_addr) << endl;
};

cs457::tcpUserSocket::tcpUserSocket(){

};

void cs457::tcpUserSocket::setSocket(int sckt)  
{ 
    userSocket=sckt;
};

int cs457::tcpUserSocket::connectToServer()
{
    struct sockaddr* serverPointer = tcpUserSocket::getServerAddressPointer();

    return connect(tcpUserSocket::userSocket,(struct sockaddr*)&(tcpUserSocket::serverAddress),sizeof(tcpUserSocket::serverAddress));
};


socklen_t cs457::tcpUserSocket::getLenghtPointer()
{
    socklen_t len = sizeof(userAddress);  
    return len;
};

int cs457::tcpUserSocket::getSocket()
{
    return userSocket;
}; 
int cs457::tcpUserSocket::closeSocket()
{
    return close(userSocket);
}; 

void cs457::tcpUserSocket::setUserInfoIPv4(string address, uint16_t port)
{
    clientAddressIPv4 = address;
    clientPortIPv4 = port; 
}; 

std::tuple<string,ssize_t> cs457::tcpUserSocket::recvString(int bufferSize, bool useMutex)
{
    char stringBuffer[bufferSize]; 
    memset(stringBuffer, 0, sizeof(stringBuffer));    //change made here. Zeros out buffer.

    ssize_t recvMsgSize;

    if (useMutex)
    {
        lock_guard<mutex> lock(recvMutex);
        recvMsgSize = recv(userSocket, stringBuffer, bufferSize, 0); 
    }    
    else
    {
        recvMsgSize = recv(userSocket, stringBuffer, bufferSize, 0); 
    }
    
    
   
    return make_tuple(string(stringBuffer),recvMsgSize);     
};
        

ssize_t cs457::tcpUserSocket::sendString(const string & data, bool useMutex)
{
    //https://stackoverflow.com/questions/7352099/stdstring-to-char
    if (data.size() == 0) return 0;                 
    int bufferSize = data.size()+1; 
    vector<char> stringBuffer(data.c_str(), data.c_str() + data.size() + 1u);

    ssize_t rval; 
    if (useMutex)
    {
       lock_guard<mutex> lock(sendMutex);
       rval = send(userSocket, &stringBuffer[0], bufferSize, 0);
    }
    else
    {
       rval = send(userSocket, &stringBuffer[0], bufferSize, 0);     
    }

    return rval;
};

string cs457::tcpUserSocket::getUniqueIdentifier()
{ 
    //this unique identifier is arbitrary 
    //and it may not be useful for chat program (see other classes)
    //it has not been tested to be unique but for now, we don't need it. 
     string identifier  = "[" + clientAddressIPv4 + "," + to_string(clientPortIPv4) + "]"; 
     return identifier; 
};

struct sockaddr * cs457::tcpUserSocket::getAddressPointer()
{
    return ((struct sockaddr *) &userAddress);
};

struct sockaddr * cs457::tcpUserSocket::getServerAddressPointer()
{
    return ((struct sockaddr *) &serverAddress);
}