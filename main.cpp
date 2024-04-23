#include <fstream>
#include <iostream>
#include <string>

// do not include utils. They are to be linked via project utils.
#include "tickethandler.h"

using namespace std;

int main()
{
    ifstream myfile;

    string line;
    char temp;
    // REPLACE EB04706280 with other file name.
    myfile.open("EB04706280.csv", ifstream::in);
    while (myfile.good()) {
        temp = (char)myfile.get();
        if (temp != '\n') {
            line += temp;
        } else {
            cout << line << endl;
            line = "";
        }
    }
    myfile.close();

    return 0;
}
