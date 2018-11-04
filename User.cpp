#include "User.h"

using namespace std;
User::User(){
}

void User::setNick(const string nick){
    nickName = nick;
}

void User::setPass(const string pass){
    password = pass;
}

void User::setTcpUserSocket(cs457::tcpUserSocket *socket){
    socketConnection = socket;
}

cs457::tcpUserSocket& User::getTcpUserSocket(){
    return *socketConnection;
}

bool User::checkPass(const string passAttempt){
    if(password == passAttempt){
        return true;
    }
    else{
        return false;
    }
}









