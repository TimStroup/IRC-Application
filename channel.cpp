#include "channel.h"

using namespace std;

channel::channel(string name){
    channel::name = name;
};

string channel::getName(){

    return channel::name;
};

void channel::setTopic(string topic){
    channel::topic = topic;
};

void channel::addUser(User *user){
    channel::channelParticipants.push_back(user);
};

void channel::removeUser(string nickName){
    for(int i = 0; i < channelParticipants.size();i++){
        if(nickName == channelParticipants.at(i)->getNick()){
            channelParticipants.erase(channelParticipants.begin() + i);
        }
    }
};

