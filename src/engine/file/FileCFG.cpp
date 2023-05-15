#define __MT_FILE_CFG_CPP__

#include <sstream>
#include <fstream>

#include "common.h"
#include "FileCFG.h"

#include "engine/exception/LoadException.h"

using namespace std;
using namespace mt;


FileCFG::FileCFG(string filename)
{
	load(filename);
}

FileCFG::~FileCFG()
{
}

string FileCFG::get(string key)
{
	if (m_data.find(key) == m_data.end())
		return "";
	return m_data.at(key);
}

bool FileCFG::getBool(string key)
{
	string data = get(key);
	if (!data.length())
		return false;
	if (!(data == "true"))
		return false;
	return true;
}

int FileCFG::getInt(string key)
{
	string data = get(key);
	if (!data.length())
		return 0;
	stringstream geek(data);
	int x = 0;
	geek >> x;
	return x;
}

uint FileCFG::getUInt(string key)
{
	string data = get(key);
	if (!data.length())
		return 0;
	stringstream geek(data);
	uint x = 0;
	geek >> x;
	return x;
}

float FileCFG::getFloat(string key)
{
	string data = get(key);
	if (!data.length())
		return 0.0f;
	stringstream geek(data);
	float x = 0;
	geek >> x;
	return x;
}

vec3 FileCFG::getVec3(string key)
{
	string data = get(key);
	if (!data.length())
		return vec3();
	stringstream geek(data);
	float x, y, z;
	geek >> x >> y >> z;
	return vec3(x, y, z);
}

map<string, string>* FileCFG::getPtr()
{
	return &m_data;
}

void FileCFG::load(string filename)
{
	ifstream fCFG;
	fCFG.open(filename.c_str(), ios::in);
	if (!fCFG.is_open())
		throw LoadException("Can't read file: " + filename, __FILE__, __LINE__);
	
	string line;
	vector<string> sessionKey, sessionValue;
	while (!fCFG.eof())
	{
		getline(fCFG, line);
		if (line.length() == 0 || line[0] == ';')
			continue;

		int pos = line.find("=");
		m_data.insert(pair<string, string>(line.substr(0, pos), line.substr(pos+1, line.length()-pos-1)));
	}
	fCFG.close();
}
