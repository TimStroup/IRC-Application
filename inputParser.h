#include <string>
#include <vector>


using namespace std;
class InputParser{

    public:
        InputParser (int &argc, char **argv);
        const string& getCmdOption(const string &option) const;
        bool cmdOptionExists(const string &option) const;

    private:
        vector <string> tokens;

};