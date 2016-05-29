#ifndef OR_H_
#define OR_H_
#include "base.h"
class Or: public Base {
    private:
    Base* child1; //variable
    Base* child2;
	public:
        Or(Base* ch1, Base* ch2) { //constructor
            child1 = ch1;
            child2 = ch2;
            return;
        }
        ~Or() { //destructor
            delete child1;
            delete child2;
            return;
        }
		void execute() {
            //if child1 succeeds, child2 is not exeucted, and the status is 
            //changed to false
			if (!(child1->getSuccess()))
			{
			    if (child2->getExecutable() != "exit") {
            	    child2->execute();
				    this->setSuccess(child2->getSuccess());	
                }
                else {
                    this->setSuccess(true);
                }
			}

			else
			{
				this->setSuccess(true);
				child2->setSuccess(false);

			}

		}

        string getExecutable() {
            return child2->getExecutable();
        }
};
#endif
