#ifndef BASE_H
#define BASE_H
#include <string>
using namespace std;
class Base {
	private:
		bool success;
        bool executed;
	public:
		Base() {};
        virtual ~Base() {};
		virtual void execute() = 0;
        virtual string getExecutable() = 0;
        virtual bool getChildSuccess() = 0;
	    virtual bool getSuccess(){

			return success;			
		}

		virtual void setSuccess(bool input){

			success = input;
		}
        void setExecuted(bool hi) {
            executed = hi;
        }
        bool getExecuted() {
            return executed;
        }
};
#endif
