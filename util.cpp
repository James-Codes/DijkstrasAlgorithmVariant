//Dijkstra's Algorithm Implementation

#include <iostream>
#include <string>
#include "util.h"
#include <sstream>
using namespace std;

//***FUNCTION THAT TAKES IN COMMAND AND SELECTS CORRESPONDING DECISION (PARSER)***
string nextCommand(int *s, int *d, int *f) {

    string command; //object that will be returned, a string object with a copy of the current contents
    //in the stream buffer
    string stream1; //for 1st part of stream
    string stream2; //for 2nd part of stream

    while (1) {      //initiates while loop that runs until break

        getline(cin, command);
        //declaring istringstream
        std::istringstream iss (command);

        //search for the string find in user input
        if (command.find("find") != string::npos)
        {

            iss >> stream1 >> *s >> *d >> *f;
            command = stream1;
            return command;
        }

        //search for the string write in user input
        if (command.find("write") != string::npos)
        {

            iss >> stream1 >> stream2 >> *s >> *d;
            //concatenate the two streams and set equal to command
            command = stream1 + " " + stream2;
            return command;
        }

        //search for the string stop in user input
        if (command == "stop") {
            return command;
        }

        break;
    }
    return command;
}
