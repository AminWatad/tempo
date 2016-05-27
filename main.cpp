#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include "base.h"
#include "command.h"
#include "and.h"
#include "or.h"
#include <vector>
using namespace std;

int main() {
    bool run = true; //bool to check if exit was inputed
    string input; //variable to get the input line from
    string cmd1 = ""; //variable to fill while parsing
    string cmd2 = ""; //variable to fill in case we had and, or condition
    string check; //variable to check next word to proccess from stringstream
    string user; //string to hold the name of the logged in used
    string hostname; //string to hold the name of the host machine
    string check2; //same as check1
    int counter = 0; //keeps track of how many words in the string stream
    vector<Base*> cmds; //vector to hold the commands to be executed
    FILE *in;
    unsigned exit_cnt = 0;
    char name[20]; //array to hold a command
    in = popen("whoami", "r"); //runs the command "whoami" and holds the output
    while(fgets(name, sizeof(name), in) != NULL) { //copies the value from file
        user = name;
    }
    char host[30];
    in = popen("hostname -s", "r");
    while(fgets(host, sizeof(host), in) != NULL) {
        hostname = host;
    }
    user.erase(user.length() - 1); //deletes the newline from the string
    hostname.erase(hostname.length() - 1); //same as previous
    while(run) { //while loop checks if exit was entered
        counter = 0;
        exit_cnt = 0;
        cout << user << "@" << hostname << "$ "; //prints the username each tim
        getline(cin, input); //gets the line of input
        stringstream iss(input); //string stream to parse the input
        while(iss >> check) { //while loop to check if the ss is not empty
            ++counter;
            if(check.at(check.length() - 1) == ';'){ //searches for ;
                check.erase(check.length() - 1); //deletes the ; from cmd
                if(!check.empty()) { //checks if there is a command b4 the ;
                    cmd1 += " ";
                    cmd1 += check; //adds the new word to the command
                }
                if(check == "exit") {
                    exit_cnt = cmds.size();
                    run = false;
                }
                else {
                    cmds.push_back(new Command(cmd1));
                     //adds command to the vector
                }
                cmd1 = ""; //empties string for future input
                cmd2 = "";
            }
            else if (check.at(0) == '#') { //checks if we have a command
                break; //exits the nested while since after # nothing matters
            }
            else if (check == "&&") { //checks if we have and condition
                //if vector is empty we push back first condition
                if(cmd1 != "") cmds.push_back(new Command(cmd1));
                stringstream iss2(input);
                //another ss to check for later words w/o incremneting the first
                for (int i = 0; i < counter; ++i) {
                    iss2 >> check2;
                    } //incremints the ss to where the first reached

                while(iss2 >> check2) { //checks what is after the and command
                    char comment = check2.at(0);
                    if(!(check2 == "&&" || check2 == "||" || comment == '#')) {
                        iss >> check;
                        ++counter;
                    }
                    if(check2 == "&&" || check2 == "||") {
                        Command* CMD2 = new Command(cmd2);
                        cmds.push_back(new And(cmds.at(cmds.size() - 1),CMD2));
                        cmd1 = "";
                        cmd2 = "";
                        break;
                    }
                    else if(check2.at(0) == '#') {
                        Command* CMD2 = new Command(cmd2);
                        cmds.push_back(new And(cmds.at(cmds.size() - 1), CMD2));
                        cmd1 = "";
                        cmd2 = "";
                        break;
                    }
                    else if(check2.at(check2.length() - 1) == ';') {
                        check2.erase(check2.length() - 1);
                        if(cmd2 != "") cmd2 += " ";
                        cmd2 += check2;
                        Command* CMD2 = new Command(cmd2);
                        cmds.push_back(new And(cmds.at(cmds.size() - 1), CMD2));
                        cmd1 = "";
                        cmd2 = "";
                        break;
                    }
                    else{
                        if(cmd2 != "") cmd2 += " ";
                        cmd2 += check2;
                    }
                }
                if ((!cmd1.empty()) || (!cmd2.empty())) {
                Command * CMD2 = new Command(cmd2);
                cmds.push_back(new And(cmds.at(cmds.size() - 1), CMD2));
                cmd1 = "";
                cmd2 = "";
                }
                if (!(iss2 >> check2)) {
                    break;
                }
            }
            else if (check == "||") {
                 if (cmd1 != "") cmds.push_back(new Command(cmd1));
                stringstream iss2(input);
                for (int i = 0; i < counter; ++i) {
                    iss2 >> check2;
                    }

                while(iss2 >> check2) {
                    char comment = check2.at(0);
                    if(!(check2 == "&&" || check2 == "||" || comment == '#')) {
                         iss >> check;
                         ++counter;
                    }
                    if(check2 == "&&" || check2 == "||") {
                        Command* CMD2 = new Command(cmd2);
                        cmds.push_back(new Or(cmds.at(cmds.size() - 1),CMD2));
                        cmd1 = "";
                        cmd2 = "";
                        break;
                    }
                    else if(check2.at(0) == '#') {
                        Command* CMD2 = new Command(cmd2);
                        cmds.push_back(new Or(cmds.at(cmds.size() - 1), CMD2));
                        cmd1 = "";
                        cmd2 = "";
                        break;
                    }
                    else if(check2.at(check2.length() - 1) == ';') {
                        check2.erase(check2.length() - 1);
                        if(cmd2 != "") cmd2 += " ";
                        cmd2 += check2;
                        Command* CMD2 = new Command(cmd2);
                        cmds.push_back(new Or(cmds.at(cmds.size() - 1), CMD2));
                        cmd1 = "";
                        cmd2 = "";
                        break;
                    }
                    else{
                        if(cmd2 != "") cmd2 += " ";
                        cmd2 += check2;
                    }
                }
                if((!cmd1.empty()) || (!cmd2.empty())) {
                    Command * CMD2 = new Command(cmd2);
                    cmds.push_back(new Or(cmds.at(cmds.size() - 1), CMD2));
                    cmd1 = "";
                    cmd2 = "";
                }
                if(!(iss2 >> check2)) {
                    break;
                }
            }
            else if(check == "exit") { //changes to bool to false to exit
                run = false;
                exit_cnt = cmds.size();
            }
            else { //if there are no &&, ||, ;, # add the string to the cmd
                if(cmd1 != "") cmd1 += " ";
                cmd1 += check;
            }
        }
        if(cmd1 != "") { //if there are no && || etc, and str not empty,adds cmd
            cmds.push_back(new Command(cmd1));
            cmd1 = "";
        }
        if (run) exit_cnt = cmds.size();
        if (run || (exit_cnt != 0)) { 
            //if exit hasn't been entered, executes commands
            for(unsigned i = 0; i < exit_cnt; ++i) {
                cmds.at(i)->execute();
                if (cmds.at(i)->getSuccess() && cmds.at(i)->getExecutable() == "exit") {
                    run = false;
                    break;
                }
            }
            while(!cmds.empty()) cmds.pop_back(); //empties the vector afte exec
        }
        input = "";
    }

    return 0;

}
    
