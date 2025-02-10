#define __MT_EXCEPTION_CPP__

#include <sstream>

#include "common.h"
#include "Exception.h"

using namespace mt;

Exception::Exception() {
	this->message = "";
	// this->files = "";
	// this->lines = 0;
}

Exception::Exception(std::string _code, std::string _msg, std::string _file, int _line) {
	this->code = _code;
	this->message = _msg;
	this->files.push_back(_file);
	this->lines.push_back(_line);
}

Exception::~Exception() {

}

std::string Exception::getCode() {
	return this->code;
}
std::string Exception::getMessage() {
	std::stringstream strBuild;

	// Print Tracker
	for (int i=this->files.size()-1; i>=0; i--)
		strBuild << "[" << this->files.at(i) << ": " << this->lines.at(i) << "] " << std::endl;

	// Print Message
	strBuild << "[" << this->code << "] " << this->message;

	return strBuild.str();
}

void Exception::setMessage(std::string _code, std::string _msg) {
	this->code = _code;
	this->message = _msg;
}

void Exception::addTrack(std::string _file, int _line) {
	this->files.push_back(_file);
	this->lines.push_back(_line);
}
