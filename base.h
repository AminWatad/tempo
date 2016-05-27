#ifndef BASE_H
#define BASE_H
#include <string>
using namespace std;
class Base {
	private:
		bool success;
	public:
		Base() {};
        virtual ~Base() {};
		virtual void execute() = 0;
        virtual string getExecutable() = 0;
	    virtual bool getSuccess(){

			return success;			
		}

		virtual void setSuccess(bool input){

			success = input;
		}
};
#endif
