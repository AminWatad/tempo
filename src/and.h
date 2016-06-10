#ifndef AND_H
#define AND_H
#include "base.h"
#include <iostream>
using namespace std;
class And: public Base{
    private:
        Base* child1; //private var
        Base* child2;
	public:
        And(Base* ch1, Base* ch2) { //constructors
            child1 = ch1;
            child2 = ch2;
            return;
        }
        ~And() { //destructor, destroys pointers
            delete child1;
            delete child2;
            return;
        }
		void execute(){ //if child1 succeeds, child2 is executed, else child2
                        //is not executed, and status is changed to false

            child1->execute();

			if (child1->getSuccess())
			{
                //if child1 succeeds, child 2 is executed
                if (child2->getExecutable() != "exit") {
				    child2->execute();
                    this->setSuccess(child2->getSuccess());
                }
                else {
                    child2->execute();
                    this->setSuccess(child1->getSuccess());
                }
			}
			else
			{
				this->setSuccess(false);
				child2->setSuccess(false);

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
