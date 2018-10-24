//input parser written by iain on stack overflow, link: https://stackoverflow.com/questions/865668/how-to-parse-command-line-arguments-in-c
//#include "inputParser.h"
#include <string>
#include <vector>  
#include <algorithm>
#include <iostream>

using namespace std;
class InputParser{
    public:
        InputParser (int &argc, char **argv){
            for (int i=1; i < argc; ++i)
                this->tokens.push_back(string(argv[i]));
        }
        /// @author iain
        const string& getCmdOption(const string &option) const{
            vector<string>::const_iterator itr;
            itr =  find (this->tokens.begin(), this->tokens.end(), option);
            if (itr != this->tokens.end() && ++itr != this->tokens.end()){
                return *itr;
            }
            static const string empty_string("");
            return empty_string;
        }
        /// @author iain
        bool cmdOptionExists(const string &option) const{
            return find (this->tokens.begin(), this->tokens.end(), option)
                   != this->tokens.end();
        }
    private:
        vector <string> tokens;
};

