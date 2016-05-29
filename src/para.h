#ifndef PARA_H
#define PARA_H
#include "base.h"
#include <vector>
class Para: public Base {
    
    private:
        vector<Base*> commands;

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
            }
            if (!oneIsFalse) this->setSuccess(true);
        }
        string getExecutable() {
            return "nothing";
        }
		
};
#endif
