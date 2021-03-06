#include "commandManager.h"
#include <time.h>
#include "Parsing.h"
#include <iostream>
#include <fstream>
#include <vector>
#include "channel.h"
#include "User.h"

using namespace std;

commandManager::commandManager(User* clientUser1, vector<User*>* chatClientUsers1, vector<channel*> *channels,string dbPath) {
    commandManager::clientUser = clientUser1;
    commandManager::chatClientUsers = chatClientUsers1;
    commandManager::channels = channels;
    commandManager::dbPath = dbPath;
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
        return commandManager::invite(messageParameters);
    }
    else if(commandString == "ISON") {
        return commandManager::ison(messageParameters);
    }
    else if(commandString == "JOIN") {
        return commandManager::join(messageParameters);
    }
    else if(commandString == "KICK") {
        return commandManager::kick(messageParameters);
    }
    else if(commandString == "KILL") {
        return commandManager::kill(messageParameters);
    }
    else if(commandString == "KNOCK") {
        return commandManager::knock(messageParameters);
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
        return commandManager::notice(messageParameters);
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
        return commandManager::privmsg(messageParameters, false);
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
    else if(commandString == "LOGIN"){
        commandManager::login(messageParameters);
    }
    else if(commandString == "REGISTER"){
        commandManager::registerUser(messageParameters);
    }
    else {
        clientUser->socketConnection->sendString("Command does not exist");
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
bool commandManager::invite(vector<string> parameters) {
    //Ensure that there is both a User and a Channel in the parameters
    if(parameters.size() == 2) {

        //Check if the user exist or not
        int index = checkForUser(parameters.at(0));

        //Default of -1 means user DOES NOT Exist. If user does exist, then
        //index was updated.
        if(index != -1) {

            //Check that the next parameter is really a channel or not
            if(parameters.at(1).at(0) == '#' || parameters.at(1).at(0) == '&') {
                string sendString = "You have been invited to join " + 
                                    parameters.at(1) +
                                    " by " + clientUser->getNick();
                chatClientUsers->at(index)->socketConnection->sendString(sendString);
                clientUser->socketConnection->sendString("Invitiation Sent to: " + parameters.at(0));
            } else {
                clientUser->socketConnection->sendString("Improper format for Channel");
            }

        } else {
            clientUser->socketConnection->sendString("User does not exist");
        }
    } else {
        clientUser->socketConnection->sendString("Invalid number of parameters");
    }
    return true;
}
bool commandManager::ison(vector<string> parameters) {
    //Check to see if a parameter (a comma separated string) was passed in or not.
    if(parameters.size() == 1) {
        vector<string> listOfClients;

        //Create a vector of the clients that are being checked on
        listOfClients = parseCommaList(parameters.at(0));
        
        //The eventual return string
        string onlineClients = "List of online client(s): ";

        //First, we loop through all the clients that are being asked about
        for(int i = 0; i < listOfClients.size(); i++) {
            int index = -1;

            //As we grab a client that is being asked about, we check all of the online
            //users in chatClientUsers. If that user is found in the list, update the
            //index so that we know that we found it.
            index = checkForUser(listOfClients.at(i));

            //As long as the index was updated, it means the user in question is online
            //and we append their name to the return string.
            if(index != -1) {
                onlineClients += chatClientUsers->at(index)->getNick();
                onlineClients += ",";
            }
        
        }

        onlineClients.pop_back(); //Remove trailing comma

        clientUser->socketConnection->sendString(onlineClients);
    } else {
        clientUser->socketConnection->sendString("Invalid number of parameters");
    }
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
            channel *channel = channels->at(channelIndex);
            if(channels->at(channelIndex)->getPassword() != ""){
                if(passwordGiven){
                    if(key == channels->at(channelIndex)->getPassword()){
                        if(userInChannel(channel)){
                            clientUser->socketConnection->sendString("Already a part of the channel: " + channel->getName());
                        }
                        else{
                            channels->at(channelIndex)->addUser(clientUser);
                            clientUser->socketConnection->sendString("success:" + channelString + ": connected to channel");
                        }
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
                if(userInChannel(channel)){
                    clientUser->socketConnection->sendString("Already a part of the channel: " + channel->getName());
                }
                else{
                    channels->at(channelIndex)->addUser(clientUser);
                    clientUser->socketConnection->sendString("success:" + channelString +": connected to channel");
                }
                
            }
            
        }
        else{
            channel *createdChannel;
            if(passwordGiven){
                createdChannel = new channel(channelString, key);
                clientUser->socketConnection->sendString("success:" + channelString + ": Created and connected to channel with password: " + key);
            }
            else{
                createdChannel = new channel(channelString,"");
                clientUser->socketConnection->sendString("success:" + channelString + ": Created and connected to channel");
            }
            
            createdChannel->addUser(clientUser);
            channels->push_back(createdChannel);
        }
    return true;
}

bool commandManager::kick(vector<string> parameters) {
    
    //Check that there is a channel and a user to perform the operation on
    if(parameters.size() == 2) {
        
        string targetChannel = parameters.at(0);
        string targetClient = parameters.at(1);

        int channelIndex = -1;

        //Check that the channel exist or not
        if(checkForChannel(targetChannel, channelIndex)) {

            //Find out if the user is a part of the channel or not
            User* userInQuestion = channels->at(channelIndex)->getUser(targetClient);
            if(userInQuestion != nullptr) {
                channels->at(channelIndex)->removeUser(targetClient);
            } else {
                clientUser->socketConnection->sendString("User is not in channel");
            }
        } else {
            clientUser->socketConnection->sendString("Channel does not exist");
        }
    } else {
        clientUser->socketConnection->sendString("Invalid number of parameters");
    }
    return true;
}
bool commandManager::kill(vector<string> parameters) {
        
    //Make sure we have both a client to kill and a message to send
    if(parameters.size() == 2) {

        string targetClient = parameters.at(0);
        string message = parameters.at(1);

        //Check if user exist. default is -1 for non exisint clients
        int index = checkForUser(targetClient);

        //Send the message of why the user is being killed. Then force them to QUIT
        if(index != -1) {
            chatClientUsers->at(index)->socketConnection->sendString(message);
            chatClientUsers->at(index)->socketConnection->sendString("QUIT");
            //chatClientUsers->at(index)->socketConnection->closeSocket();
        } else {
        clientUser->socketConnection->sendString("User does not exist");
        }
    } 
    else {
        clientUser->socketConnection->sendString("Invalid number of parameters");
    }

    return true;

}

bool commandManager::knock(vector<string> parameters) {
    
    //Check if there is Channel to knock
    if(parameters.size() == 1) {
        
        string targetChannel = parameters.at(0);
        int channelIndex;

        //Check that the channel exist or not
        if(checkForChannel(targetChannel,channelIndex)) {
            string message = "User [" + clientUser->getNick() + "] is requesting to join: " + targetChannel;
            channels->at(channelIndex)->sendMessage(message);
        } else {
            clientUser->socketConnection->sendString("Channel does not exist");
        }

    // Else, there is a channel and a message to send as they are knocking
    } else if (parameters.size() == 2) {
        
        string targetChannel = parameters.at(0);
        string knockMessage = parameters.at(1);

        int channelIndex;

        if(checkForChannel(targetChannel,channelIndex)) {
        
            string message = "User [" + clientUser->getNick() + "] is requesting to join: " + targetChannel + '\n'
            + "Their message is: " + knockMessage;
            channels->at(channelIndex)->sendMessage(message);
        
        } else {
            clientUser->socketConnection->sendString("Channel does not exist");
        }
    } else {
        clientUser->socketConnection->sendString("Invalid number of parameters");
    }
}
bool commandManager::list(vector<string> parameters) {

    if(channels->size() != 0) {
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

            channelList = parseCommaList(parameters.at(0));
        
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
    } else {
        clientUser->socketConnection->sendString("There are no channels currently");
    }
    
    return true;
}

bool commandManager::mode() {
    cout << "Mode() command called" << endl;

}
bool commandManager::nick(vector<string> parameters) {
    clientUser->setNick(parameters.at(0));
    clientUser->socketConnection->sendString("Now using Nick: " + parameters.at(0));
    return true;

}
bool commandManager::notice(vector<string> messageParameters) {

    //Check if there is a user and a message to be passed in
    if(messageParameters.size() == 2) {
        messageParameters.at(1).insert(0, "[NOTICE]: ");
        commandManager::privmsg(messageParameters, true);
    } else {
        clientUser->socketConnection->sendString("Invalid number of paramters");
    }
    return true;
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
bool commandManager::privmsg(vector<string>messageParameters, bool isNotice) {
    
    //Check if there is both a User/Channel to send to, and a message to send, thus size = 2
    if(messageParameters.size() == 2) {
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
            index = checkForUser(targetClient);

            //If the nick was found, the index was updated to point to their location in the
            //vector. Grab the tcpUserSocket of that nick and send the message that was passed in
            if(index != -1) {
            
                cs457::tcpUserSocket& targetSocket = chatClientUsers->at(index)->getTcpUserSocket();
                string finalMessage = "[" + clientUser->getNick() + "]: " + msg; 
                targetSocket.sendString(finalMessage);
                clientUser->socketConnection->sendString(finalMessage);
            
                //If the user is away, reply automatically with their away message
                if(chatClientUsers->at(index)->getAwayStatus() == true && isNotice == false) {
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
    string currentUsers = "Current Online Users: ";

    for(int i = 0; i < chatClientUsers->size(); i++) {
        currentUsers += chatClientUsers->at(i)->getNick();
        currentUsers += ",";
    }

    currentUsers.pop_back();

    clientUser->socketConnection->sendString(currentUsers);
    
    return true;
}
bool commandManager::version() {
    string versionString = "Server version: 1.0.0 \nAuthors: Tim Stroup and Trey Yu";
    clientUser->socketConnection->sendString(versionString);

    return true;
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

bool commandManager::login(vector<string> messageParameters){
    if(messageParameters.size() < 1){
        clientUser->socketConnection->sendString("Must provide at least nickname to login, nickname and password if the account is password protected");
        return true;
    }

    string loginNickname = messageParameters.at(0);
    string loginPassword;
    string level = "";
    string banned = "";
    bool success = false;
    if(messageParameters.size() == 1){
        loginPassword = '@';
    }
    else{
        loginPassword = messageParameters.at(1);
    }

    ifstream fileIn((dbPath + "users.txt"));
    string line;
    while(getline(fileIn,line)){
        string userName;
        stringstream fileLine(line);
        getline(fileLine,userName,' ');
        if(loginNickname == userName){
            string password;
            getline(fileLine,password,' ');
            if(password == loginPassword){
                success = true;
                getline(fileLine,level,' ');
                getline(fileLine,banned,' ');
            }
        }
    }
    if(success){
        if(level == "ADMIN"){
            clientUser->setLevel(User::Level::ADMIN);
        }
        else if(level == "SYSOP"){
            clientUser->setLevel(User::Level::SYSOP);
        }
        else if(level == "CHANNELOP"){
            clientUser->setLevel(User::Level::CHANNELOP);
        }
        else{
            clientUser->setLevel(User::Level::USER);
        }

        clientUser->setNick(loginNickname);

        clientUser->socketConnection->sendString("Succesfully logged in to account with nickname: " + loginNickname);
    }
    else{
        clientUser->socketConnection->sendString("Failed to validate with account nickname: " + loginNickname + " and Password: " + loginPassword);
    }

}

bool commandManager::registerUser(vector<string> messageParameters){
    string loginNickname = "";
    string loginPassword = "@";

    if(messageParameters.size() < 1){
        clientUser->socketConnection->sendString("Must provide at least nickname to register, nickname and password if you want the account to be password protected");
        return true;
    }

    loginNickname = messageParameters.at(0);
    if(messageParameters.size() >= 2){
        loginPassword = messageParameters.at(1);
    }

    ifstream fileIn((dbPath + "users.txt"));
    string line;
    while(getline(fileIn,line)){
        string userName;
        stringstream fileLine(line);
        getline(fileLine,userName,' ');
        if(loginNickname == userName){
            clientUser->socketConnection->sendString("User already exists with nickname: " + loginNickname + " try another");
            return true;
        }
    }
    fileIn.close();
    //otherwise the file did not contain a matching nickname and one can now be created by appending to the end of the file
    ofstream addUser((dbPath + "users.txt"),ios::app);
    addUser << loginNickname + " " + loginPassword + " " + "USER" + " " + "false" + "\n";
    if(loginPassword == "@"){
        clientUser->socketConnection->sendString("Succesfully registerd account with Nickname: " + loginNickname + " and no Password");

    }
    else{
        clientUser->socketConnection->sendString("Succesfully registerd account with Nickname: " + loginNickname + " and Password: " + loginPassword);

    }




    
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

vector<string> commandManager::parseCommaList(string& commaList) {
    vector<string> returnVector;
    string tempString;
    istringstream iss(commaList);

    while(getline(iss,tempString, ',')) {
        returnVector.push_back(tempString);
    }

    return returnVector;
}

int commandManager::checkForUser(string user) {
    int index = -1;

    for(int i = 0; i < chatClientUsers->size(); i++) {
        if(chatClientUsers->at(i)->getNick() == user) {
            index = i;
        }
    }

    return index;
}

bool commandManager::userInChannel(channel* channel){
    if(channel->getUser(clientUser->getNick()) == nullptr){
        return false;
    }
    else{
        return true;
    }
}
