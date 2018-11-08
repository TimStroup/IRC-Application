#include "commandManager.h"
#include <time.h>
#include "Parsing.h"
#include <iostream>
#include <vector>
#include "channel.h"

using namespace std;

commandManager::commandManager(User* clientUser1, vector<User*>* chatClientUsers1, vector<channel*> *channels) {
    commandManager::clientUser = clientUser1;
    commandManager::chatClientUsers = chatClientUsers1;
    commandManager::channels = channels;
}

bool commandManager::handleCommand(const string &command, vector<string> parameters) {

    Parsing::IRC_message ircMessage(command);

    string commandString = ircMessage.command;
    vector<string> messageParameters = ircMessage.params;

    if(commandString == "AWAY") {
        return commandManager::away(messageParameters);
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
        return commandManager::join(messageParameters);
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
    else if(commandString == "LIST") {
        return commandManager::list(messageParameters);
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
        return commandManager::time(messageParameters);
    }
    else if(commandString == "TOPIC") {
        return commandManager::topic(messageParameters);
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
bool commandManager::away(vector<string> parameters) {
    if(parameters.size() == 0) {
        clientUser->setAwayStatus(false);
        clientUser->setAwayMessage("");
    } else {
        clientUser->setAwayStatus(true);
        clientUser->setAwayMessage(parameters.at(0));
    }

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
bool commandManager::join(vector<string> parameters) {
    if(parameters.size() < 1){
        clientUser->socketConnection->sendString("Must Provide Channel like: Join <channel>[optional<space><pass>]");
        return true;
    }
    cout << parameters.size() << endl;
    
    string channelString = parameters.at(0);
    string key;
    bool passwordGiven = false;

    
    if(parameters.size() > 1){
       key = parameters.at(1);
       passwordGiven = true;
    }

    //check for correct channel format
    if(channelString.at(0) != '#' && channelString.at(0) != '&'){
        clientUser->socketConnection->sendString("Channel name must be prefixed with a \'#\' or \'&\'");
        return true;
    }

    //check for channel existence, if it exists add the user to the channel, if not create the channel and add the user
        int channelIndex = -1;
        bool channelExists = checkForChannel(channelString, channelIndex);

        if(channelExists){
            if(channels->at(channelIndex)->getPassword() != ""){
                if(passwordGiven){
                    if(key == channels->at(channelIndex)->getPassword()){
                        channels->at(channelIndex)->addUser(clientUser);
                        clientUser->socketConnection->sendString("connected to channel: " + channelString);
                    }
                    else{
                        clientUser->socketConnection->sendString("Password incorrect for channel: " + channelString);
                    }
                }
                else{
                    clientUser->socketConnection->sendString("No password provided for password protected channel: " + channelString);
                }
            }
            else{
                channels->at(channelIndex)->addUser(clientUser);
                clientUser->socketConnection->sendString("connected to channel: " + channelString);
            }
            
        }
        else{
            channel *createdChannel;
            if(passwordGiven){
                createdChannel = new channel(channelString, key);
                clientUser->socketConnection->sendString("Created and connected to channel: " + channelString + " with password: " + key);
            }
            else{
                createdChannel = new channel(channelString,"");
                clientUser->socketConnection->sendString("Created and connected to channel: " + channelString);
            }
            
            createdChannel->addUser(clientUser);
            channels->push_back(createdChannel);
        }
    return true;
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
bool commandManager::list(vector<string> parameters) {
    //If parameter size == 0, LIST was passed in without channel names,
    // so just print out all the current channels
    if(parameters.size() == 0) {
        string channelList;
        for(int i = 0; i < channels->size(); i++) {
            channelList += channels->at(i)->getName() + ",";
        }
        channelList.pop_back(); //Removes trailing comma
        clientUser->socketConnection->sendString("Current Channels are: " + channelList);
    } 
    //Else, if parameter size == 1, a comma separated string containing channel
    // names were passed. Parse through the string and return the topic of each
    // of the specified channels
    else if(parameters.size() == 1) {
        
        vector<string> channelList;
        string channelInQuestion;

        istringstream channelStream(parameters.at(0));

        //Process the comma separated string and add those channels to a vector
        while (getline(channelStream, channelInQuestion, ',')) {
            channelList.push_back(channelInQuestion);
        }

        string topicList;
        int channelIndex;

        //For each of the channels in the passed in string, check if they exist or not.
        //If they do, grab their topic, and add it to the response string
        for(int i = 0; i < channelList.size(); i++) {
            if(checkForChannel(channelList.at(i), channelIndex)) {
                string tempString = "Channel [" + channelList.at(i) + "] topic is: " + channels->at(channelIndex)->getTopic() + ",";
                topicList += tempString;
            }
        }

        topicList.pop_back(); //Removes trailing comma

        clientUser->socketConnection->sendString(topicList);
    }  
    //Else, the wrong number of parameters were passed in.
    else {
        clientUser->socketConnection->sendString("Invalid number of parameters");
    }
    
    return true;
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
    commandManager::pong();

}
bool commandManager::pong() {
    clientUser->socketConnection->sendString("Pong");

}
bool commandManager::privmsg(vector<string>messageParameters) {
    
    //Check if there is both a User/Channel to send to, and a message to send, thus size = 2
    if(messageParameters.size() >= 2) {
        string targetClient = messageParameters.at(0);
        string msg = messageParameters.at(1);

        bool isChannel = false;

        if(targetClient.at(0) == '&' || targetClient.at(0) == '#') {
            isChannel = true;
        }

        //After verifying that the target was a channel, make sure that channel exist
        if(isChannel) {
            int channelIndex = -1;
            bool channelExists = checkForChannel(targetClient, channelIndex);

            //If channel existence is verified, proceed to send message to that channel
            if(channelExists) {
                string finalMessage = "[" + targetClient + "-" + clientUser->getNick() + "]: " + msg;
                channels->at(channelIndex)->sendMessage(finalMessage);
            } else {
                clientUser->socketConnection->sendString("Channel [" + targetClient + "] does not exist");
            }
        }else {
            //MASSIVE ELSE!!!!! This Else handles NON CHANNEL Messages (IE Direct Private Messages)

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
                string finalMessage = "[" + clientUser->getNick() + "]: " + msg; 
                targetSocket.sendString(finalMessage);
            
                //If the user is away, reply automatically with their away message
                if(chatClientUsers->at(index)->getAwayStatus() == true) {
                    string awayMessage = "User is away: " + chatClientUsers->at(index)->getAwayMessage();
                    clientUser->getTcpUserSocket().sendString(awayMessage);
                } else {
                // Do Nothing, the user is not away
                }
            }else {
                cout << "User does not exist" << endl;
                clientUser->socketConnection->sendString("User does not exist");
            }
        }
    } else {
        cout << "Invalid number of parameters passed in for PRIVMSG" << endl;
    }

    return true;
}
bool commandManager::quit(vector<string>messageParameters) {
    cout << "Quit command called" << endl;
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
bool commandManager::time(vector<string> parameters) {
    time_t timer;

    std::time(&timer);
    string currentTime(ctime(&timer));

    string finalMessage = "[SERVER REPLY] Current Time is: " + currentTime;
    clientUser->socketConnection->sendString(finalMessage);

    return true;
}
bool commandManager::topic(vector<string> parameters) {
    bool channelExists = false;
    int channelIndex = -1;
    
    if(parameters.size() == 1) {
        
        channelExists = checkForChannel(parameters.at(0), channelIndex);

        if(channelExists) {
            clientUser->socketConnection->sendString("Topic of [" + parameters.at(0) + "] is: " + channels->at(channelIndex)->getTopic());
        }else {
            clientUser->socketConnection->sendString("Channel does not exist");
        }

    } else if(parameters.size() == 2) {
        
        channelExists = checkForChannel(parameters.at(0), channelIndex);
        
        if(channelExists) {
            channels->at(channelIndex)->setTopic(parameters.at(1));
            clientUser->socketConnection->sendString("Topic of [" + parameters.at(0) + "] has been set to: " + parameters.at(1));
        }else {
            clientUser->socketConnection->sendString("Channel does not exist");
        }

    } else {
        clientUser->socketConnection->sendString("Invalid number of parameters passed in");
    }

    return true;
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

//SUPPORT FUNCTIONS

bool commandManager::checkForChannel(string channelName, int& channelIndex) {
    for(int i = 0; i < channels->size(); i++) {
        if(channels->at(i)->getName() == channelName) {
            channelIndex = i;
            return true;
        }
    }
    return false;
}

