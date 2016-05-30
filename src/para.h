#ifndef PARA_H
#define PARA_H
#include "base.h"
#include <vector>
class Para: public Base {
    
    private:
        vector<Base*> commands;
        string executable;

	public:
        Para(vector<Base*> V) {
            for (int i = 0; i < V.size(); ++i) {
                commands.push_back(V.at(i));
            }
            return;
        }
        ~Para() {
            while (!commands.empty()) commands.pop_back();
        }
		void execute() {
            bool oneIsFalse = false;
            for (int i = 0; i < commands.size(); ++i) {
                commands.at(i)->execute();
                if (!commands.at(i)->getSuccess()) oneIsFalse = true;
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
