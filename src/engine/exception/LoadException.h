#ifndef __MT_LOAD_EXCEPTION_H__
#define __MT_LOAD_EXCEPTION_H__

#include "Exception.h"

namespace mt {

class LoadException : public Exception {

public:

	// Forward
	LoadException();
	LoadException(std::string msg, std::string file, int line);
	~LoadException();

	// Native

	// Stock

private:

	// Variable

};

}

#endif
