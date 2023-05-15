#define __MT_LOAD_EXCEPTION_CPP__

#include <sstream>

#include "common.h"
#include "LoadException.h"

using namespace mt;

LoadException::LoadException()
{
}

LoadException::LoadException(std::string _msg, std::string _file, int _line)
{
	this->message = _msg;
	this->file = _file;
	this->line = _line;
}

LoadException::~LoadException()
{

}
