#pragma once
#include <string>
#include <vector>
#include "User.h"

using namespace std;
class channel
{
    public: 
    channel(string name, string password);
    string getName();
    string getPassword();
    void setTopic(string topic);
    void addUser(User *user);
    void removeUser(string nickName);
    void sendMessage(string message);
    User* getUser(string nickName);

    private:
    string name;
    string topic;
    string password;
    vector<User *> channelParticipants;
};