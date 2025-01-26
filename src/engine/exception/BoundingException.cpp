#define __MT_BOUNDING_EXCEPTION_CPP__

#include <sstream>

#include "common.h"
#include "BoundingException.h"

using namespace std;
using namespace mt;

BoundingException::BoundingException()
{
}

BoundingException::BoundingException(string _msg, string _file, int _line)
{
	this->message = _msg;
	// this->files = _file;
	// this->lines = _line;
}

BoundingException::~BoundingException()
{
}
