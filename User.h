#pragma once
#include <string>
#include "tcpUserSocket.h"

using namespace std;
class User
{
    public:
        User();
        User(const string nick, shared_ptr<cs457::tcpUserSocket> socket);
        enum Level {ADMIN,SYSOP,USER,CHANNELOP};
        void setNick(const string nick);
        void setPass(const string pass);
        bool checkPass(const string passAttempt);
        const string getNick();
        void setTcpUserSocket(shared_ptr<cs457::tcpUserSocket> socket);
        void setAwayStatus(bool);
        void setAwayMessage(string);
        bool getAwayStatus();
        void setLevel(Level);
        Level getLevel();
        string getAwayMessage();
        cs457::tcpUserSocket& getTcpUserSocket();
        cs457::tcpUserSocket *socketConnection;
        
        
    
    private:
        string nickName;
        string password;
        string awayMessage;
        bool isBanned;
        bool awayStatus = false;
        Level accountLevel = USER;
        
};