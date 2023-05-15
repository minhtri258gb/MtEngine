#ifndef __MT_MATH_EXCEPTION_H__
#define __MT_MATH_EXCEPTION_H__

#include "Exception.h"

namespace mt {

class MathException : public Exception {

public:

	// Forward
	MathException();
	MathException(std::string msg, std::string file, int line);
	~MathException();

	// Native

	// Stock

private:

	// Variable

};

}

#endif
