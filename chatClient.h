#include "inputParser.h"
#include "tcpUserSocket.h"


using namespace std; 
    class chatClient{
    public:
    void setNickname(string& nickname);
    const string& getNickname();
    


    private:
    string nickName;
    string password;
    tcpUserSocket tcpUserSocket;

    };