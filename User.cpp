#include "User.h"

using namespace std;


User::User(const string nick, shared_ptr<cs457::tcpUserSocket> socket) {
    User::setNick(nick);
    User::setTcpUserSocket(socket);
}
void User::setNick(const string nick){
    nickName = nick;
}

void User::setPass(const string pass){
    password = pass;
}

void User::setTcpUserSocket(shared_ptr<cs457::tcpUserSocket> socket){
    socketConnection = socket.get();
}

const string User::getNick() {
    return nickName;
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









