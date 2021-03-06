#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include "base.h"
#include "command.h"
#include "and.h"
#include "or.h"
#include "piping.h"
#include "para.h"
#include <vector>
using namespace std;
//the main file has two parsing function, one of commands without priority
//the other with priority
//This function creates an object and passes the commands as a vector after
//parsing.
Base* priority( string input ) {
    string cmd1 = ""; //variable to fill while parsing
    string cmd2 = ""; //variable to fill in case we had and, or condition
    string check; //variable to check next word to proccess from stringstream 
    stringstream iss(input); //string stream to parse the input
    vector<Base*> cmds;
    string check2 = "";
    int counter = 0;
    while(iss >> check) { //while loop to check if the ss is not empty
        ++counter;
        if(check.at(check.length() - 1) == ';'){ //searches for ;
            check.erase(check.length() - 1); //deletes the ; from cmd
            if(!check.empty()) { //checks if there is a command b4 the ;
                cmd1 += " ";
                cmd1 += check; //adds the new word to the command
            }
            cmds.push_back(new Command(cmd1));
                //adds command to the vector
            
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
                    //in case && was faced, we create another string stream
                    //so we don't interfere with the primary one
                    if(!(check2 == "&&" || check2 == "||" || comment == '#')) {
                        iss >> check;
                        ++counter;
                    }
                    //these conditions check when the second child ends
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
                //in case the command didn't end in one of those conditions
                //we push it to the commands vector
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
                //this condition is very identical to previous one but deals 
                //with || condition
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
            else { //if there are no &&, ||, ;, # add the string to the cmd
                if(cmd1 != "") cmd1 += " ";
                cmd1 += check;
            }
        }
        if ( cmd1 != "" ) cmds.push_back(new Command(cmd1));
        Para* vec = new Para(cmds);
        return vec;
}
    
int main() {
    bool run = true; //bool to check if exit was inputed
    string input; //variable to get the input line from
    string user; //string to hold the name of the logged in used
    string hostname; //string to hold the name of the host machine
    vector<Base*> cmds; //vector to hold the commands to be executed
    vector<string> commands;
    string command;
    string check1;
    FILE *in;
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
        cout << user << "@" << hostname << "$ "; //prints the username each tim
        getline(cin, input); //gets the line of input
        stringstream iss(input); //string stream to parse the input
        bool stop = false;
        while(iss >> check1) { //while loop to check if the ss is not empty
            //these condition push commands into a vector of strings
            //to be later analyzed and passed to the right object

            if ((check1.at(check1.length() - 1) == ';') && !stop) {
                //in case we had a semi colon, we stop and push the command
                check1.erase(check1.length() - 1);
                if (command != "" && check1 != "") {
                    command += " ";
                    command += check1;
                }
                else command += check1;
                commands.push_back(command);
                command = "";
            }
            else if (check1.at(0) == '(') { 
                //change stop to true so other condition don't stop the 
                //parsing before the end which is )
                command = check1;
                stop = true;
            }
            else if (check1.find(')') != -1) {
                //this means the parentheses are closed and we move on to next
                //command
                if (check1.at(check1.length() - 1) == ';') check1.erase(check1.length() - 1);
                stop = false;
                command += " ";
                command += check1;
                commands.push_back(command);
                command = "";
            }
            else if ((check1 == "||" || check1 == "&&" || check1 == "<" || check1 == ">" || check1 == ">>" || check1 ==  "|") && !stop) {
                if (command != "") commands.push_back(command);
                command = "";
                commands.push_back(check1);
            }
            else if (check1.at(0) == '#') {
                //comments break the parsing since nothing matters after
                if (command != "") commands.push_back(command);
                command = "";
                break;
            }
            else {
                //if nothing indicates the command is finished, we keep going
                if (command != "") command += " ";
                command += check1;
            }
        }
        //in case the command didn't end with ;, (), #,
        if (command != "") {
            commands.push_back(command);
            command = "";
        }
        bool connecterPre = false; //bool to check if this child is connected
        //This loop iterates through the vector of strings, and commands
        //are pushed to the final vector as objects depending on their priority
        //and independence
        for (unsigned i = 0; i < commands.size(); ++i) {
            if (commands.at(i) == "&&" || commands.at(i) == "||") { 
                //this means the next string would be dependent on the previous
                connecterPre = true;
            }
            else if ( commands.at(i) == "<" || commands.at(i) == ">") {
                connecterPre = true;
            }
            else if ( commands.at(i) == ">>" || commands.at(i) == "|") {
                connecterPre = true;
            }
            else if ( commands.at(i).at(0) == '(' ) {
                //if we have parentheses, we send the string to be parsed
                //but before then, we remove the parentheses for right output
                string cleanCmd = commands.at(i);
                cleanCmd.erase(0, 1);
                cleanCmd.erase( cleanCmd.length() - 1, 1 );
                Base* temp = priority(cleanCmd);
                //now the whole string is back as an object
                //the next few conditions determine if the parntheses
                //are connected to AND or OR
                if ( cmds.size() > 0  && i != 0) { 
                    if (commands.at(i - 1) == "&&") {

                        cmds.push_back(new And(cmds.at(cmds.size() - 1), temp));
                        connecterPre = false;
                    }
                    else if (commands.at(i - 1) == "||") {
                        cmds.push_back(new Or(cmds.at(cmds.size() - 1), temp));
                        connecterPre = false;
                    }
                    else cmds.push_back(temp);
                }
                else cmds.push_back(temp);
            }
            else if (connecterPre) {
                if (commands.at(i - 1) == "&&") {
                    Base* cmdTemp = new Command(commands.at(i));
                    cmds.push_back(new And(cmds.at(cmds.size() - 1), cmdTemp));
                }
                else if (commands.at(i - 1) == "||") {
                    Base* cmdTemp = new Command(commands.at(i));
                    cmds.push_back(new Or(cmds.at(cmds.size() - 1), cmdTemp));
                }
                else if (commands.at(i - 1) == "|") {
                    cmds.at(cmds.size() - 1)->setExecuted(true);
                    Base* cmdTemp = new Command(commands.at(i));
                    cmds.push_back(new Piping(cmds.at(cmds.size() - 1), cmdTemp));
                    connecterPre = false;
                }
            }
                
            else cmds.push_back(new Command(commands.at(i)));
        }
        //now we empty the vector of strings for upcoming commands
        while (!commands.empty()) commands.pop_back();
        //the last loop is to execute the line, and check if exit was entered
        for(unsigned i = 0; i < cmds.size(); ++i) {
            cmds.at(i)->execute();
            if (cmds.at(i)->getSuccess() && cmds.at(i)->getExecutable() == "exit") {
                run = false;
                break;
            }
        }
        //commands are deletes for future commands
        while(!cmds.empty()) cmds.pop_back(); //empties the vector afte exec
        input = "";
    }

    return 0;

}
    
