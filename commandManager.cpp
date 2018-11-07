#include "commandManager.h"
#include "Parsing.cpp"
#include <iostream>
#include <vector>

using namespace std;

commandManager::commandManager(User* clientUser1, vector<User*>* chatClientUsers1) {
    commandManager::clientUser = clientUser1;
    commandManager::chatClientUsers = chatClientUsers1;
}

bool commandManager::handleCommand(const string &command, vector<string> parameters) {

    Parsing::IRC_message ircMessage(command);

    string commandString = ircMessage.command;
    vector<string> messageParameters = ircMessage.params;

    if(commandString == "AWAY") {
        return commandManager::away();
    }
    else if(commandString == "CONNECT") {
        return commandManager::connect();
    }
    else if(commandString == "DIE") {
        return commandManager::die();
    }
    else if(commandString == "HELP") {
        return commandManager::help();
    }
    else if(commandString == "INFO") {
        return commandManager::info();
    }
    else if(commandString == "INVITE") {
        return commandManager::invite();
    }
    else if(commandString == "ISON") {
        return commandManager::ison();
    }
    else if(commandString == "JOIN") {
        return commandManager::join();
    }
    else if(commandString == "KICK") {
        return commandManager::kick();
    }
    else if(commandString == "KILL") {
        return commandManager::kill();
    }
    else if(commandString == "KNOCK") {
        return commandManager::knock();
    }
    else if(commandString == "MODE") {
        return commandManager::mode();
    }
    else if(commandString == "NICK") {
        return commandManager::nick(messageParameters);
    }
    else if(commandString == "NOTICE") {
        return commandManager::notice();
    }
    else if(commandString == "PART") {
        return commandManager::part();
    }
    else if(commandString == "OPER") {
        return commandManager::oper();
    }
    else if(commandString == "PASS") {
        return commandManager::pass();
    }
    else if(commandString == "PING") {
        return commandManager::ping();
    }
    else if(commandString == "PONG") {
        return commandManager::pong();
    }
    else if(commandString == "PRIVMSG") {
        return commandManager::privmsg(messageParameters);
    }
    else if(commandString == "QUIT") {
        return commandManager::quit(messageParameters);
    }
    else if(commandString == "RESTART") {
        return commandManager::restart();
    }
    else if(commandString == "RULES") {
        return commandManager::rules();
    }
    else if(commandString == "SETNAME") {
        return commandManager::setName();
    }
    else if(commandString == "SILENCE") {
        return commandManager::silence();
    }
    else if(commandString == "TIME") {
        return commandManager::time();
    }
    else if(commandString == "TOPIC") {
        return commandManager::topic();
    }
    else if(commandString == "USER") {
        return commandManager::user();
    }
    else if(commandString == "USERHOST") {
        return commandManager::userHost();
    }
    else if(commandString == "USERIP") {
        return commandManager::userip();
    }
    else if(commandString == "USERS") {
        return commandManager::users();
    }
    else if(commandString == "VERSION") {
        return commandManager::version();
    }
    else if(commandString == "WALLOPS") {
        return commandManager::wallops();
    }
    else if(commandString == "WHO") {
        return commandManager::who();
    }
    else if(commandString == "WHOIS") {
        return commandManager::whois();
    }
    else {
        cout << "Command Doesn't Exist" << endl;
        return true;
    }
}
bool commandManager::away() {
    return true;
}
bool commandManager::connect() {
    cout << "Connect() command called" << endl;
}
bool commandManager::die() {
    cout << "Die() command called" << endl;

}
bool commandManager::help() {
    cout << "Help() command called" << endl;

}
bool commandManager::info() {
    cout << "Info() command called" << endl;

}
bool commandManager::invite() {
    cout << "Invite() command called" << endl;

}
bool commandManager::ison() {
    cout << "Ison() command called" << endl;

}
bool commandManager::join() {
    cout << "Join() command called" << endl;

}
bool commandManager::kick() {
    cout << "Kick() command called" << endl;

}
bool commandManager::kill() {
    cout << "Kill() command called" << endl;

}
bool commandManager::knock() {
    cout << "Knock() command called" << endl;

}
bool commandManager::list() {
    cout << "List() command called" << endl;

}
bool commandManager::mode() {
    cout << "Mode() command called" << endl;

}
bool commandManager::nick(vector<string> parameters) {
    clientUser->setNick(parameters.at(0));
    return true;

}
bool commandManager::notice() {
    cout << "Notice() command called" << endl;

}
bool commandManager::part() {
    cout << "Part() command called" << endl;

}
bool commandManager::oper() {
    cout << "Oper() command called" << endl;

}
bool commandManager::pass() {
    cout << "Pass() command called" << endl;

}
bool commandManager::ping() {
    cout << "Ping() command called" << endl;

}
bool commandManager::pong() {
    cout << "Pong() command called" << endl;

}
bool commandManager::privmsg(vector<string>messageParameters) {
    
    //Check if there is both a User to send to, and a message to send, thus size = 2
    if(messageParameters.size() >= 2) {
        string targetClient = messageParameters.at(0);
        string msg = messageParameters.at(1);

        int index = -1; //Default to -1 so that we can check for whether the user exist or not

        //Loop through all the current chat client users and see if the nick passed in
        //is connected or not.
        for(int i = 0; i < chatClientUsers->size(); i++) {
            if(chatClientUsers->at(i)->getNick() == targetClient) {
                index = i;
            }
        }

        //If the nick was found, the index was updated to point to their location in the
        //vector. Grab the tcpUserSocket of that nick and send the message that was passed in
        if(index != -1) {
            cs457::tcpUserSocket& targetSocket = chatClientUsers->at(index)->getTcpUserSocket();
            targetSocket.sendString(msg);
        }else {
            cout << "User does not exist" << endl;
            clientUser->socketConnection->sendString("User does not exist");
        }

    } else {
        cout << "Invalid number of parameters passed in for PRIVMSG" << endl;
    }

    return true;
}
bool commandManager::quit(vector<string>messageParameters) {
    clientUser->socketConnection->sendString("QUIT");
    return false;
    
}
bool commandManager::restart() {
    cout << "Restart() command called" << endl;


}
bool commandManager::rules() {
    cout << "Rules() command called" << endl;

}
bool commandManager::setName() {
    cout << "SetName() command called" << endl;

}
bool commandManager::silence() {
    cout << "Silence() command called" << endl;

}
bool commandManager::time() {
    cout << "Time() command called" << endl;

}
bool commandManager::topic() {
    cout << "Topic() command called" << endl;

}
bool commandManager::user() {
    cout << "User() command called" << endl;

}
bool commandManager::userHost() {
    cout << "UserHost() command called" << endl;

}
bool commandManager::userip() {
    cout << "UserIp() command called" << endl;

}
bool commandManager::users() {
    cout << "Users() command called" << endl;

}
bool commandManager::version() {
    cout << "Version() command called" << endl;

}
bool commandManager::wallops() {
    cout << "Wallops() command called" << endl;

}
bool commandManager::who() {
    cout << "Who() command called" << endl;

}
bool commandManager::whois() {
    cout << "Whois() command called" << endl;

}