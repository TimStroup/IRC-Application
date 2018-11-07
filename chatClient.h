#pragma once
#include "tcpUserSocket.h"
#include <string>
#include "inputParser.cpp"

using namespace std; 
    class chatClient{
    public:
        string status;
        chatClient();
        chatClient(string& hostname, string& nickname, int port,
                    string& configFile, string& testFile, string& logFile);
        void setNickname(string& nickname);
        void setCmdFields(InputParser input);
        void receiveMessages(cs457::tcpUserSocket*);
        const string& getNickname();

    private:
        string hostname;
        string nickname;
        int port;
        string confFile;
        string testFile;
        string logFile;
        string password;

        cs457::tcpUserSocket tcpUserSocket(string server,int port);

    };