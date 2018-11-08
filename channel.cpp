#include "channel.h"

using namespace std;

channel::channel(string name, string password){
    channel::name = name;
    channel::password = password;
};

string channel::getName(){

    return channel::name;
};

string channel::getPassword(){
    return channel::password;
}

string channel::getTopic() {
    return channel::topic;
}

void channel::setTopic(string topic){
    channel::topic = topic;
};

void channel::addUser(User *user){
    channel::channelParticipants.push_back(user);
};

User* channel::getUser(string nickName){
    int index = -1;
    for(int i = 0; i < channelParticipants.size();i++){
        if(nickName == channelParticipants.at(i)->getNick()){
            index = i;
        }
    }
    //if the nickname is in the channel, return the user. otherwise return a nullptr
    if(index != -1){
        return channelParticipants.at(index);
    }
    else{
        return nullptr;
    }
}

void channel::sendMessage(string message){
    for(auto user : channelParticipants){
        user->socketConnection->sendString(message);
    }
}

void channel::removeUser(string nickName){
    for(int i = 0; i < channelParticipants.size();i++){
        if(nickName == channelParticipants.at(i)->getNick()){
            channelParticipants.erase(channelParticipants.begin() + i);
        }
    }
};

