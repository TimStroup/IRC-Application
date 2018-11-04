#include "commandManager.h"
#include "Parsing.cpp"
#include <iostream>
#include <vector>

using namespace std;

commandManager::commandManager() {
    cout << "Constructor Built" << endl;
}

bool commandManager::handleCommand(const string &command, vector<string> parameters) {
    cout << "This is the initial pass: " << command << endl;

    Parsing::IRC_message ircMessage(command);

    cout << "This is the COMMAND: " << ircMessage.command << endl;
    string commandString = ircMessage.command;

    if(commandString == "AWAY") {
        commandManager::away();
    }
    else if(commandString == "CONNECT") {
        commandManager::connect();
    }
    else if(commandString == "DIE") {
        commandManager::die();
    }
    else if(commandString == "HELP") {
        commandManager::help();
    }
    else if(commandString == "INFO") {
        commandManager::info();
    }
    else if(commandString == "INVITE") {
        commandManager::invite();
    }
    else if(commandString == "ISON") {
        commandManager::ison();
    }
    else if(commandString == "JOIN") {
        commandManager::join();
    }
    else if(commandString == "KICK") {
        commandManager::kick();
    }
    else if(commandString == "KILL") {
        commandManager::kill();
    }
    else if(commandString == "KNOCK") {
        commandManager::knock();
    }
    else if(commandString == "MODE") {
        commandManager::mode();
    }
    else if(commandString == "NICK") {
        commandManager::nick();
    }
    else if(commandString == "NOTICE") {
        commandManager::notice();
    }
    else if(commandString == "PART") {
        commandManager::part();
    }
    else if(commandString == "OPER") {
        commandManager::oper();
    }
    else if(commandString == "PASS") {
        commandManager::pass();
    }
    else if(commandString == "PING") {
        commandManager::ping();
    }
    else if(commandString == "PONG") {
        commandManager::pong();
    }
    else if(commandString == "PRIVMSG") {
        commandManager::privmsg();
    }
    else if(commandString == "QUIT") {
        commandManager::quit();
    }
    else if(commandString == "RESTART") {
        commandManager::restart();
    }
    else if(commandString == "RULES") {
        commandManager::rules();
    }
    else if(commandString == "SETNAME") {
        commandManager::setName();
    }
    else if(commandString == "SILENCE") {
        commandManager::silence();
    }
    else if(commandString == "TIME") {
        commandManager::time();
    }
    else if(commandString == "TOPIC") {
        commandManager::topic();
    }
    else if(commandString == "USER") {
        commandManager::user();
    }
    else if(commandString == "USERHOST") {
        commandManager::userHost();
    }
    else if(commandString == "USERIP") {
        commandManager::userip();
    }
    else if(commandString == "USERS") {
        commandManager::users();
    }
    else if(commandString == "VERSION") {
        commandManager::version();
    }
    else if(commandString == "WALLOPS") {
        commandManager::wallops();
    }
    else if(commandString == "WHO") {
        commandManager::who();
    }
    else if(commandString == "WHOIS") {
        commandManager::whois();
    }
    else {
        cout << "Command Doesn't Exist" << endl;
    }
    return true;
}
bool commandManager::away() {
    cout << "Away() command called" << endl;
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
bool commandManager::nick() {
    cout << "Nick() command called" << endl;

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
bool commandManager::privmsg() {
    cout << "Privmsg() command called" << endl;

}
bool commandManager::quit() {
    cout << "Quit() command called" << endl;

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