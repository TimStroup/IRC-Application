#pragma once
#include <string>
#include <vector>
#include "User.h"
#include "channel.h"

using namespace std;
class commandManager
{
  public:
    User* clientUser;
    vector<User*>* chatClientUsers;
    vector<channel*>* channels;
    string dbPath;
    commandManager(User* user, vector<User*>* chatClientUsers, vector<channel*>* activeUsers,string dbPath);
    bool handleCommand(const string &command, vector<string> paramaters);

  private:
    /* Command: AWAY
         Parameters: [message]

         With the AWAY message, clients can set an automatic reply string for
         any PRIVMSG commands directed at them (not to a channel they are on).
        */
    bool away(vector<string>);

    /*Command: CONNECT
        Parameters: <target server> [<port> [<remote server>]]

        The CONNECT command can be used to force a server to try to establish
        a new connection to another server immediately.  CONNECT is a
        privileged command and is to be available only to IRC Operators. 
        */
    bool connect();

    /*
        Syntax: DIE
        Instructs the server to shut down. 
        This command may only be issued by IRC server operators.
        */
    bool die();

    /*
        Syntax: HELP
        Requests the server to display the help file. 
        This command is not formally defined in an RFC, but is in use by most major IRC daemons.
        */
    bool help();

    /*
        Syntax: INFO [<target>]
        Returns information about the <target> server, or the current server if <target> is omitted.
         Information returned includes the server’s version, when it was compiled, the patch level, 
         when it was started, and any other information which may be considered to be relevant. 
        */
    bool info();

    /*
        Syntax: INVITE <nickname> <channel>
        Invites <nickname> to the channel <channel>.
         <channel> does not have to exist, but if it does, only members of the channel are allowed to invite other clients. 
         If the channel mode i is set, only channel operators may invite other clients. 
        */
    bool invite(vector<string>);

    /*
        Syntax: ISON <nicknames>
        Queries the server to see if the clients in the space-separated list <nicknames> are currently on the network.
         The server returns only the nicknames that are on the network in a space-separated list. 
         If none of the clients are on the network the server returns an empty list.
        */
    bool ison(vector<string>);

    /*
        Syntax: JOIN <channels> [<keys>]
        Makes the client join the channels in the comma-separated list <channels>, specifying the passwords, if needed, in the comma-separated list <keys>.
        If the channel(s) do not exist then they will be created. 
        */
    bool join(vector<string>);

    /*
        Syntax: KICK <channel> <client> [<message>]
        Forcibly removes <client> from <channel>.This command may only be issued by channel operators.
        */
    bool kick(vector<string>);

    /*
        Syntax: KILL <client> <comment>
        Forcibly removes <client> from the network. This command may only be issued by IRC operators. 
        */
    bool kill(vector<string>);

    /*
        Syntax: KNOCK <channel> [<message>]
        Sends a NOTICE to an invitation-only <channel> with an optional <message>, requesting an invite. 
        This command is not formally defined by an RFC, but is supported by most major IRC daemons. 
        Support is indicated in a RPL_ISUPPORT reply (numeric 005) with the KNOCK keyword.
        */
    bool knock(vector<string>);

    /*
        Syntax: LIST [<channels> [<server>]]
        Lists all channels on the server. If the comma-separated list <channels> is given, it will return the channel topics. 
        If <server> is given, the command will be forwarded to <server> for evaluation. 
        */
    bool list(vector<string>);

    /*
        Syntax:
        MODE <nickname> <flags> (user)
        MODE <channel> <flags> [<args>]
        
        The MODE command is dual-purpose. It can be used to set both user and channel modes.
        */
    bool mode();

    /*
        Syntax: 
        NICK <nickname> (RFC 2812)
        Allows a client to change their IRC nickname.
        */
    bool nick(vector<string> parameters);

    /*
        Syntax: NOTICE <msgtarget> <message>
        This command works similarly to PRIVMSG, except automatic replies must never be sent in reply to NOTICE messages.
        */
    bool notice();

    /*
        Syntax: PART <channels> [<message>]
        Causes a user to leave the channels in the comma-separated list <channels>
        */
    bool part();

    /*
        Syntax: OPER <username> <password>
        Authenticates a user as an IRC operator on that server/network.
        */
    bool oper();

    /*
        Syntax: PASS <password>
        Sets a connection password. This command must be sent before the NICK/USER registration combination. 
        */
    bool pass();

    /*
        Syntax: PING <server1> [<server2>]
        Tests the presence of a connection. A PING message results in a PONG reply. 
        If <server2> is specified, the message gets passed on to it.
        */
    bool ping();

    /*
        Syntax: PONG <server1> [<server2>]
        This command is a reply to the PING command and works in much the same way.
        */
    bool pong();

    /*
        Syntax: PRIVMSG <msgtarget> <message>
        Sends <message> to <msgtarget>, which is usually a user or channel
        */
    bool privmsg(vector<string>);

    /*
        Syntax: QUIT [<message>]
        Disconnects the user from the server.
        */
    bool quit(vector<string>);

    /*
        Syntax: RESTART
        Restarts a server. It may only be sent by IRC operator.
        */
    bool restart();

    /*
        Syntax: RULES
        Requests the server rules. This command is not formally defined in an RFC, but is used by most
        */
    bool rules();

    /*
        Syntax: SETNAME <new real name>
        Allows a client to change the "real name" specified when registering a connection.
        This command is not formally defined by an RFC, but is in use by some IRC daemons. 
        Support is indicated in a RPL_ISUPPORT reply (numeric 005) with the SETNAME keyword
        */
    bool setName();

    /*
        Syntax: SILENCE [+/-<hostmask>]
        Adds or removes a host mask to a server-side ignore list that prevents matching users from sending the client messages. 
        More than one mask may be specified in a space-separated list, each item prefixed with a "+" or "-" to designate whether it is being added or removed. 
        Sending the command with no parameters returns the entries in the client’s ignore list.
        */
    bool silence();

    /*
        Syntax: TIME [<server>]
        Returns the local time on the current server, or <server> if specified.
        */
    bool time(vector<string>);

    /*
        Syntax: TOPIC <channel> [<topic>]
        Allows the client to query or set the channel topic on <channel>. 
        If <topic> is given, it sets the channel topic to <topic>. 
        If channel mode +t is set, only a channel operator may set the topic.
        */
    bool topic(vector<string>);

    /*
        Syntax:
        USER <username> <hostname> <servername> <realname> (RFC 1459)
        USER <user> <mode> <unused> <realname> (RFC 2812)

        This command is used at the beginning of a connection to specify the username, hostname, real name and initial user modes of the connecting client.
         <realname> may contain spaces, and thus must be prefixed with a colon.
        */
    bool user();

    /*
        Syntax: USERHOST <nickname> [<nickname> <nickname> ...]
        Returns a list of information about the nicknames specified.
        */
    bool userHost();

    /*
        Syntax: USERIP <nickname>
        Requests the direct IP address of the user with the specified nickname. 
        This command is often used to obtain the IP of an abusive user to more effectively perform a ban. 
        It is unclear what, if any, privileges are required to execute this command on a server.
        */
    bool userip();

    /*
        Syntax: USERS [<server>]
        Returns a list of users and information about those users in a format similar to the UNIX commands who, rusers and finger.
        */
    bool users();

    /*
        Syntax: VERSION [<server>]
        Returns the version of <server>, or the current server if omitted.
        */
    bool version();

    /*
        Syntax: WALLOPS <message>
        Sends <message> to all operators connected to the server.
        */
    bool wallops();

    /*
        Syntax: WHO [<name> ["o"]]
        Returns a list of users who match <name>. 
        If the flag "o" is given, the server will only return information about IRC operators.
        */
    bool who();

    /*
        Syntax: WHOIS [<server>] <nicknames>
        Returns information about the comma-separated list of nicknames masks <nicknames>.
         If <server> is given, the command is forwarded to it for processing.
        */
    bool whois();

    bool login(vector<string>);

    bool registerUser(vector<string>);

    //SUPPORT FUNCTIONS

    vector<string> parseCommaList(string&);
    bool checkForChannel(string, int&);
    int checkForUser(string);
    
    //check if a user is in a channel
    bool userInChannel(channel *channel);

};