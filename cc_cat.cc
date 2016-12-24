// standard simple cat program, iostream style

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char** argv) {

    // Code to get an istream& into instr.
    // Clunkier than the C FILE* version.  streams aren't copyable or
    // movable AFAIK, std::cin is an istream, you need ifstream to open
    // files.  So need a pointer; then I get a reference for further
    // use.
    ifstream infile;
    istream *instrp;
    if (argc == 2) {
        infile.open(argv[1]);
        instrp = &infile;
    }
    else
        instrp = &cin;
    auto &instr = *instrp;

    for (string s; getline(instr, s); ) {
        cout << s << "\n";
    }
}
