#ifndef __MT_BOUNDING_EXCEPTION_H__
#define __MT_BOUNDING_EXCEPTION_H__

#include "Exception.h"

namespace mt {

class BoundingException : public Exception {

public:

	// Forward
	BoundingException();
	BoundingException(std::string msg, std::string file, int line);
	~BoundingException();

	// Native

	// Stock

private:

	// Variable

};

}

#endif
