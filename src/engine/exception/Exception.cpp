#define __MT_EXCEPTION_CPP__

#include <sstream>

#include "common.h"
#include "Exception.h"

using namespace mt;

Exception::Exception()
{
	this->message = "";
	this->file = "";
	this->line = 0;
}

Exception::Exception(std::string _msg, std::string _file, int _line)
{
	this->message = _msg;
	this->file = _file;
	this->line = _line;
}

Exception::~Exception()
{

}

/*
 * Format: [file: line] message
 */
std::string Exception::getMessage()
{
	std::stringstream strBuild;
	strBuild << "[" << this->file << ": " << this->line << "] " << this->message;
	return strBuild.str();
}

void Exception::setMessage(std::string _msg, std::string _file, int _line)
{
	this->message = _msg;
	this->file = _file;
	this->line = _line;
}
