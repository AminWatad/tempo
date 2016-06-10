#ifndef PIPING_H
#define PIPING_H
#include "base.h"
#include <iostream>
using namespace std;
class Piping: public Base{
    private:
        Base* child1; //private var
        Base* child2;
	public:
        Piping(Base* ch1, Base* ch2) { //constructors
            child1 = ch1;
            child2 = ch2;
            return;
        }
        ~Piping() { //destructor, destroys pointers
            delete child1;
            delete child2;
            return;
        }
		void execute(){ //if child1 succeeds, child2 is executed, else child2
                        //is not executed, and status is changed to false
            stringstream iss1(child1->getExecutable()); //ss to hold the command
            stringstream iss2(child1->getExecutable());
            string in1;
            string in;
            int counter = 0; //counts the words in iss2 to create an array
            while(!iss1.eof()){ //process of counting
                 ++counter;
                 iss1 >> in;
            }
            this->setSuccess(true);
            char *cmd1[41]; //creates an array, +1 for NULL char
            for(int i = 0; i < counter; ++i) { //fills the array from iss2
                iss2 >> in;
                char *cstr2 = new char[in.length() + 1];
                strcpy(cstr2, in.c_str());
                cmd1[i] = cstr2;
            }
            cmd1[counter] = NULL; //adds the NULL char for the array
            stringstream iss3(child2->getExecutable()); //ss to hold the command

            stringstream iss4(child2->getExecutable());
            counter = 0; //counts the words in iss2 to create an array
            while(!iss3.eof()){ //process of counting
                 ++counter;
                 iss3 >> in1;
            }

            char *cmd2[41]; //creates an array, +1 for NULL char
            for(int i = 0; i < counter; ++i) { //fills the array from iss2
                iss4 >> in1;
                char *cstr1 = new char[in1.length() + 1];
                strcpy(cstr1, in1.c_str());
                cmd2[i] = cstr1;
            }
            cmd2[counter] = NULL; //adds the NULL char for the array
            int fd[2];
            pipe(fd);
            pid_t pid1;
            pid_t pid2;
            if (pid1 = fork() == 0) {
                dup2(fd[1], 1);
                close(fd[1]);
                close(fd[0]);
                execvp(cmd1[0], cmd1);
            } else if ((pid2 = fork()) == 0 ) {
                dup2(fd[0], 0);
                close(fd[1]);
                execvp(cmd2[0], cmd2);
            } else {
                close(fd[1]);
                waitpid(pid1, NULL, 0);
                waitpid(pid2, NULL, 0);
            }
        }

			
	
        string getExecutable() {
            //in case the command was exit
            return child2->getExecutable();
        }

        bool getChildSuccess() {
            return child2->getSuccess();
        }



};
#endif
