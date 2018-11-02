#pragma once

#include <sys/socket.h>
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <strings.h>
#include <string> 
#include <tuple> 
#include <unistd.h>
#include <assert.h>
#include <vector> 
#include <memory> 
#include <mutex>

namespace cs457
{
    using namespace std; 
    
    class tcpUserSocket
    {
        public:
            tcpUserSocket(string srvrAddress,int port);
            tcpUserSocket();
            void setSocket(int skct); 
            struct sockaddr * getAddressPointer();
            socklen_t getLenghtPointer();
            int getSocket(); 
            int closeSocket();
            std::tuple<string,ssize_t> recvString(int bufferSize=4096,bool useMutex = true);
            void setUserInfoIPv4(string clientAddress,uint16_t port);
            int connectToServer();
            ssize_t sendString(const string & data,bool useMutex = true);
            string getUniqueIdentifier();
         

        private:
        struct sockaddr_in userAddress; 
        struct sockaddr_in serverAddress;
        string serverAddressString;
        struct sockaddr * getServerAddressPointer();
        int userSocket; 
        string clientAddressIPv4; 
        uint16_t clientPortIPv4;
        mutex sendMutex;
        mutex recvMutex; 
    };

}