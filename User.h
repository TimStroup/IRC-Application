#pragma once
#include <string>
#include "tcpUserSocket.h"

using namespace std;
class User
{
    public:
        User();
        void setNick(const string nick);
        void setPass(const string pass);
        bool checkPass(const string passAttempt);
        const string getNick();
        void setTcpUserSocket(cs457::tcpUserSocket *socket);
        cs457::tcpUserSocket& getTcpUserSocket();
    
    private:
        string nickName;
        string password;
        cs457::tcpUserSocket *socketConnection;

};