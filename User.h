#pragma once
#include <string>
#include "tcpUserSocket.h"

using namespace std;
class User
{
    public:
        User();
        User(const string nick, shared_ptr<cs457::tcpUserSocket> socket);
        void setNick(const string nick);
        void setPass(const string pass);
        bool checkPass(const string passAttempt);
        const string getNick();
        void setTcpUserSocket(shared_ptr<cs457::tcpUserSocket> socket);
        cs457::tcpUserSocket& getTcpUserSocket();
        cs457::tcpUserSocket *socketConnection;

    
    private:
        string nickName;
        string password;
        
};