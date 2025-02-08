#define __MT_STRING_UTILS_CPP__

#include <stdarg.h>
#include <sstream>

#include "common.h"
#include "StringUtils.h"

using namespace std;
using namespace mt::engine;


int StringUtils::parseInt(std::string str) {
	int num;
	stringstream ss;
	ss << str;
	ss >> num;
	return num;
}

string StringUtils::format(char *fmt, ...) {
	va_list list;
	va_start(list, fmt);
	char buffer[1024];
	vsnprintf(buffer, sizeof(buffer), fmt, list);
	va_end(list);

	return string(buffer);
}

bool StringUtils::endWith(std::string str, std::string substr) {
	if (str.length() >= substr.length())
		return (0 == str.compare (str.length() - substr.length(), substr.length(), substr));
	else
		return false;
}
