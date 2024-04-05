#define __MT_FILE_PATH_UTILS_CPP__

#include "common.h"
#include "FilePathUtils.h"

using namespace std;
using namespace mt::engine;

string FilePathUtils::getExtension(string path)
{
	if (path.find_last_of(".") != string::npos)
		return path.substr(path.find_last_of(".") + 1);
	return "";
}
