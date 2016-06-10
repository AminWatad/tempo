#ifndef PARA_H
#define PARA_H
#include "base.h"
#include <vector>
class Para: public Base {
    //This class holds a vector of all of the commands between too parentheses
    //it iterates through the vector and asserts the execute function
    private:
        vector<Base*> commands; //vector of commands
        string executable; //to handle exit case

	public:
        Para(vector<Base*> V) {
            //populating the vector which was passed through the parsing func.
            for (int i = 0; i < V.size(); ++i) {
                commands.push_back(V.at(i));
            }
            return;
        }
        ~Para() {
            while (!commands.empty()) commands.pop_back();
        }
		void execute() {
            bool oneIsFalse = false; //in case one command fails, everything
                                    // between the parentheses is set to false
            for (int i = 0; i < commands.size(); ++i) {
                //executing the commands
                commands.at(i)->execute();
                if (!commands.at(i)->getSuccess()) oneIsFalse = true;
                //this if statement handles the exit case
                if (commands.at(i)->getChildSuccess() && commands.at(i)->getExecutable() == "exit") {
                    executable = "exit";
                }
            }
            if (!oneIsFalse) this->setSuccess(true);
        }
        string getExecutable() {
            if (!(executable == "exit")) executable = "nothing";
            return executable;
        }
        bool getChildSuccess() {
            return this->getSuccess();
        }
		
};
#endif
