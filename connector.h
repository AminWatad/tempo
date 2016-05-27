#ifndef CONNECTER_H
#define CONNECTER_H
#include "base.h"

class Connector: public Base {

	public:

		Connector() {};
		virtual void execute() = 0;
		


};
#endif
