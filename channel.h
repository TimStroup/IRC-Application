#pragma once
#include <string>
#include <vector>
#include "User.h"

using namespace std;
class channel
{
    public: 
    channel(string name);
    string getName();
    void setTopic(string topic);
    void addUser(User *user);
    void removeUser(string nickname);

    private:
    string name;
    string topic;
    vector<User *> channelParticipants;
};