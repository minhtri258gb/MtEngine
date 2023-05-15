#define __MT_MATH_EXCEPTION_CPP__

#include <sstream>

#include "common.h"
#include "MathException.h"

using namespace std;
using namespace mt;

MathException::MathException()
{
}

MathException::MathException(string _msg, string _file, int _line)
{
	this->message = _msg;
	this->file = _file;
	this->line = _line;
}

MathException::~MathException()
{

}
