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
	sessionID = 0;
	load(filename);
}

FileCFG::~FileCFG()
{
}

void FileCFG::select(string sessionName)
{
	short sizeArr = m_sessions.size();
	for(short i = 0; i < sizeArr; i++)
		if(m_sessions.at(i) == sessionName)
		{
			this->sessionID = i;
			return;
		}
	
	throw Exception("Session \"" + sessionName + "\" not found!", __FILE__, __LINE__);
}

string FileCFG::get(string key)
{
	// Validate
	short sizeArr = m_sessions.size();
	if (this->sessionID == sizeArr)
		return "";

	sizeArr = m_key[sessionID].size();

	for (short i = 0; i < sizeArr; i++)
		if (m_key[sessionID][i] == key)
			return m_value[sessionID][i];
			
	return "";
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

vec2 FileCFG::getVec2(string key)
{
	string data = get(key);
	if (!data.length())
		return vec3();

	stringstream geek(data);
	float x, y;
	geek >> x >> y;

	return vec2(x, y);
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

void FileCFG::load(string filename)
{
	ifstream fCFG;
	fCFG.open(filename.c_str(), ios::in);
	if (!fCFG.is_open())
		throw LoadException("Can't read file: " + filename, __FILE__, __LINE__);
	
	string line;
	vector<string> sessionKey, sessionValue;
	short session = 0;

	while (!fCFG.eof())
	{
		getline(fCFG, line);
		if (line.length() == 0 || line[0] == ';')
			continue;

		if (line[0] == '[')
		{ // session
			if (session)
			{
				m_key.push_back(sessionKey);
				m_value.push_back(sessionValue);
				sessionKey.clear();
				sessionValue.clear();
			}

			m_sessions.push_back(line.substr(1, line.length() - 2));
			session++;
		}
		else
		{
			int pos = line.find("=");
			sessionKey.push_back(line.substr(0, pos));
			sessionValue.push_back(line.substr(pos+1, line.length()-pos-1));
		}
	}
	if (session)
	{
		m_key.push_back(sessionKey);
		m_value.push_back(sessionValue);
		sessionKey.clear();
		sessionValue.clear();
	}
	fCFG.close();
}
