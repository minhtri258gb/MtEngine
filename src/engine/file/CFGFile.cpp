
#define IMPORT_ENGINE
#include "../../Main.h"

#include "../kernel/System.h"
extern System *g_pSystem;

#include "CFGFile.h"


CFGFile::CFGFile(string filename)
{
	sessionID = 0;

	load(filename);
}

CFGFile::~CFGFile()
{
}

void CFGFile::select(string sessionName)
{
	short sizeArr = m_sessions.size();
	for(short i = 0; i < sizeArr; i++)
		if(m_sessions.at(i) == sessionName)
		{
			this->sessionID = i;
			return;
		}

	cout << "[CFGFile] Session \"" << sessionName << "\" not found!" << endl;
	this->sessionID = sizeArr;
	return;
}

string CFGFile::get(string key)
{
	short sizeArr = m_sessions.size();
	if (this->sessionID == sizeArr)
		return "";

	sizeArr = m_key[sessionID].size();

	for (short i = 0; i < sizeArr; i++)
		if (m_key[sessionID][i] == key)
			return m_value[sessionID][i];

	return "";
}

bool CFGFile::getBool(string key)
{
	string data = get(key);
	if (!data.length())
		return false;

	if (!(data == "true"))
		return false;

	return true;
}

int CFGFile::getInt(string key)
{
	string data = get(key);
	if (!data.length())
		return 0;

	stringstream geek(data);
	int x = 0;
	geek >> x;
	return x;
}

float CFGFile::getFloat(string key)
{
	string data = get(key);
	if (!data.length())
		return 0.0f;

	stringstream geek(data);
	float x = 0;
	geek >> x;
	return x;
}

vec3 CFGFile::getVec3(string key)
{
	string data = get(key);
	if (!data.length())
		return vec3();

	stringstream geek(data);
	float x, y, z;
	geek >> x >> y >> z;

	return vec3(x, y, z);
}

void CFGFile::load(string filename)
{
	ifstream fCFG;
	fCFG.open(filename.c_str(), ios::in);
	if(!fCFG.is_open())
	{
		g_pSystem->error("[CFGFile] Can't read file: " + filename);
		return;
	}

	string line;
	vector<string> sessionKey, sessionValue;
	short session = 0;
	while(!fCFG.eof())
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

			m_sessions.push_back(line);
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