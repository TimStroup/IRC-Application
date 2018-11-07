#include "chatRoom.h"

using namespace std;

channel::channel(string name){
    chatRoom::name = name;
};

string channel::getName(){

    return chatRoom::name;
};

void channel::setTopic(string topic){
    chatRoom::topic = topic;
};

void channel::addUser(User *user){
    chatRoom::channelParticipants.push_back(user);
};

void channel::removeUser(string nickName){
    for(int i = 0; i < channelParticipants.size();i++){
        if(nickName == channelParticipants.at(i)->getNick()){
            channelParticipants.erase(channelParticipants.begin() + i);
        }
    }
};

