#pragma once
#include <string>
#include <vector>
#include "User.h"

using namespace std;
class chatRoom
{
    public: 
    chatRoom(string name);
    string getName();
    void setTopic(string topic);
    void addUser(User *user);
    void removeUser(string nickname);

    private:
    string name;
    string topic;
    vector<User *> chatRoomParticipants;
};