#include "chatRoom.h"

using namespace std;

chatRoom::chatRoom(string name){
    chatRoom::name = name;
};

string chatRoom::getName(){

    return chatRoom::name;
};

void chatRoom::setTopic(string topic){
    chatRoom::topic = topic;
};

void chatRoom::addUser(User *user){
    chatRoom::chatRoomParticipants.push_back(user);
}

void chatRoom::removeUser(string nickName){
    for(int i = 0; i < chatRoomParticipants.size();i++){
        if(nickName == chatRoomParticipants.at(i)->getNick()){
            chatRoomParticipants.erase(chatRoomParticipants.begin() + i);
        }
    }
}

