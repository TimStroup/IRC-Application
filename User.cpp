#include "User.h"

using namespace std;
User::User(){
}

void User::setNick(const string nick){

}

void User::setPass(const string pass){

}

void User::setTcpUserSocket(cs457::tcpUserSocket *socket){
    socketConnection = socket;
}

cs457::tcpUserSocket& User::getTcpUserSocket(){
    return *socketConnection;
}

bool User::checkPass(const string passAttempt){

}









