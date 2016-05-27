#ifndef COMMAND_H
#define COMMAND_H
#include <iostream>
#include "base.h"
#include <sstream>
#include <string>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <cstdio>
using namespace std;
class Command: public Base{

	private:
		string executable; //private variables

	public:
		Command(string input){ //constructor
		    executable = input;
            this->setSuccess(false); //in default success is false
            return;
		}
        void execute() {
            //executes the cmd, and changes success depending on status
            if(this->cmdExecute() != 2) {this->setSuccess(false);}
            else {this->setSuccess(true);}
        }

		int cmdExecute() {
            stringstream iss1(executable); //ss to hold the command
            stringstream iss2(executable);
            string in;
            int counter = 0; //counts the words in iss2 to create an array
            while(!iss1.eof()){ //process of counting
                 ++counter;
                 iss1 >> in;
            }

            char *cmds[41]; //creates an array, +1 for NULL char
            for(int i = 0; i < counter; ++i) { //fills the array from iss2
                iss2 >> in;
                char *cstr = new char[in.length() + 1];
                strcpy(cstr, in.c_str());
                cmds[i] = cstr;
            }
            cmds[counter] = NULL; //adds the NULL char for the array
            char testing[] = "test";
            string option;
            if (strcmp(cmds[0],testing) == 0) {
                if (counter < 3) option = "-e";
                else option = cmds[1];
                struct stat buf;
                if (stat(cmds[counter - 1], &buf) == -1) {
                    cout << "(False)" << endl;
                    return 1;
                }
                if (option == "-e") { 
                    cout << "(True)" << endl;
                    return 2;
                }
                else if (option == "-f") {
                    if (S_ISREG(buf.st_mode)) {
                        cout << "(True)" << endl;
                        return 2;
                    }
                    else {
                        cout << "(False)" << endl;
                        return 1;
                    }
                }
                else if (option == "-d") {
                    if (S_ISDIR(buf.st_mode)) {
                        cout << "(True)" << endl;
                        return 2;
                    }
                    else {
                        cout << "(False)" << endl;
                        return 1;
                    }
                }
            }
            else if (strncmp(cmds[0],"[",1) == 0) {
                if (counter < 4) option = "-e";
                else option = cmds[1];
                struct stat buf;
                if (stat(cmds[counter - 2], &buf) == -1) {
                    cout << "(False)" << endl;
                    return 1;
                }
                if (option == "-e") { 
                    cout << "(True)" << endl;
                    return 2;
                }
                else if (option == "-f") {
                    if (S_ISREG(buf.st_mode)) { 
                        cout << "(True)" << endl;
                        return 2;
                    }
                    else {
                        cout << "(False)" << endl;
                        return 1;
                    }
                }
                else if (option == "-d") {
                    if (S_ISDIR(buf.st_mode)) { 
                        cout << "(True)" << endl;
                        return 2;
                    }
                    else { 
                        cout << "(False)" << endl;
                        return 1;
                    }
                }
                
            }
            else{
            pid_t c;
            int status; //status of the execution
            c = fork(); //creates a fork process
            if (c == 0) { //if fork is the child, execute
                 status = 1;
                 execvp(cmds[0], cmds);
                 perror("execvp");  //if execvp returns, exit
                 exit(errno);
                 
            }
            else if (c == -1){ //if fork couldn't be created
                 perror("fork"); 
                 return -1;
            }
            else  { //if pid > 0 means fork is the parent so we wait for the ch
                if( waitpid(c, &status, WUNTRACED | WCONTINUED) == -1) {
                    perror("waitpid"); //in case waitpid failed
                    return -1;
                }
            }
            
            if (WEXITSTATUS(status) == 0) { //if exit status is 0, everything 
                                            // went okay
                return 2; //success
            }
            }
            return 0;

		}

		string getExecutable(){ //returns the command if needed
			return executable;
		
		}
};
#endif
