#define __MT_LOG_CPP__

#include "common.h"
#include "Config.h"
#include "Log.h"

using namespace std;
using namespace mt::engine;

Log Log::ins;


Log::Log() {
}

Log::~Log() {
}

void Log::l(string file, int line, string message) {
	if (Config::ins.DEBUG)
		cout << "[" << file << ':' << line << "] " << message << endl;
}
