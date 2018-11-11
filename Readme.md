# Internet Relay Chat
##### Authors: Tim Stroup and Trey Yu

This implementation is based loosely around the RFC, with most commands acheiveing the same primary objective defined in the RFC, but some with minor adjustments in use cases.

## Summary of the program

This IRC works on the premise of a server that creates a server socket and waits for clients to connect to it. Every time a client connects to the server, the server spawns a thread and creates a Command Manager to handle all message and commands that the clients sends. The Server continues to run in a while loop, waiting for input, making the server interactive. 

### Commands Implemented:
- Away
- Invite
- Ison
- Join
- Kick
- Kill
- Knock
- List
- Nick
- Notice
- Ping
- Pong
- Privmsg
- Quit
- Time
- Topic
- Users
- Version

#### Commands that were added
- Login
- RegisterUser


## Differences from the RFC

The primary difference that should be noted from our implementation and the RFC is the user registration and login procedure. Rather than calling the PASS, NICK, and USER Command to register a connection, we developed a RegisterUser and Login command. The premise behind these are simple, the RegisterUser commands takes a Nickname and Password, and writes these values to a text file called _users.txt_. The Login command takes a Nickname and Password as well, but searches the text file for the values to validate.

#### Other Minor Differences
Some commands do not behave exactly as the RFC defines them. A brief summary of each is as followed:
- Kick: Only takes two arguments instead of 3, as a message of why they are not being kicked is not being currently sent. This will be update in the next release
- Knock: Command does not take a third argument to specify <server> as we do not have multiple servers
- Quit: Does not take a message currently and clients simply exit. This will be updated in the next release.
- Users: Command does not take in any arguments, since we only have one server.
