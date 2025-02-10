#define __MT_FILE_CFG_CPP__

#include <sstream>
#include <fstream>
#include <algorithm>

#include "common.h"
#include "FileCFG.h"

using namespace std;
using namespace mt;


FileCFG::FileCFG() {
	sessionID = 0;
}
FileCFG::FileCFG(string filename) {
	sessionID = 0;
	load(filename);
}
FileCFG::~FileCFG() {
}

void FileCFG::select(string sessionName) {
	short sizeArr = m_sessions.size();
	for (short i = 0; i < sizeArr; i++) {
		if (m_sessions.at(i) == sessionName) {
			this->sessionID = i;
			return;
		}
	}

	throw error("SESSION_NOT_FOUND", "Session \"" + sessionName + "\" not found!");
}
void FileCFG::addSession(string sessionName) {
	short sizeArr = m_sessions.size();
	for (short i = 0; i < sizeArr; i++) {
		if (m_sessions.at(i) == sessionName) {
			sessionID = i;
			return;
		}
	}

	vector<string> keys, values;

	m_sessions.push_back(sessionName);
	m_key.push_back(keys);
	m_value.push_back(values);

	sessionID = m_sessions.size() - 1;
}
void FileCFG::set(string key, string value) {
	// Validate
	short sizeArr = m_sessions.size();
	if (this->sessionID == sizeArr)
		return;

	sizeArr = m_key[sessionID].size();

	// Find pos of key
	short pos = -1;
	for (short i = 0; i < sizeArr; i++) {
		if (m_key[sessionID][i] == key) {
			pos = i;
			break;
		}
	}

	if (pos >= 0) { // if found
		m_value[sessionID][pos] = value;
	}
	else { // if not found then add
		m_key[sessionID].push_back(key);
		m_value[sessionID].push_back(value);
	}
}
void FileCFG::save(string filepath) {
	fstream file(filepath, fstream::out);

	for (short i=0, szi=m_sessions.size(); i<szi; i++) {
		string session = m_sessions[i];
		file << '[' << session << ']' << endl;

		vector<string> keys = m_key[i];
		vector<string> values = m_value[i];
		for (short j=0, szj=keys.size(); j<szj; j++) {
			string key = keys[j];
			string value = values[j];

			file << key << '=' << value << endl;
		}

		file << endl;
	}

	file.close();
}

vector<string> FileCFG::keys() {
	vector<string> res;

	// Validate
	short sizeArr = m_sessions.size();
	if (this->sessionID == sizeArr)
		return res;

	res = m_key[sessionID];
	return res;
}
vector<string> FileCFG::values() {
	vector<string> res;

	// Validate
	short sizeArr = m_sessions.size();
	if (this->sessionID == sizeArr)
		return res;

	res = m_value[sessionID];
	return res;
}

string FileCFG::get(string key) {
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
bool FileCFG::getBool(string key) {
	string data = get(key);
	if (!data.length())
		return false;

	if (!(data == "true"))
		return false;

	return true;
}
int FileCFG::getInt(string key) {
	string data = get(key);
	if (!data.length())
		return 0;

	stringstream geek(data);
	int x = 0;
	geek >> x;
	return x;
}
uint FileCFG::getUInt(string key) {
	string data = get(key);
	if (!data.length())
		return 0;

	stringstream geek(data);
	uint x = 0;
	geek >> x;

	return x;
}
float FileCFG::getFloat(string key) {
	string data = get(key);
	if (!data.length())
		return 0.0f;

	stringstream geek(data);
	float x = 0;
	geek >> x;

	return x;
}
vec2 FileCFG::getVec2(string key) {
	string data = get(key);
	if (!data.length())
		return vec3();

	stringstream geek(data);
	float x, y;
	geek >> x >> y;

	return vec2(x, y);
}
vec3 FileCFG::getVec3(string key) {
	string data = get(key);
	if (!data.length())
		return vec3();

	stringstream geek(data);
	float x, y, z;
	geek >> x >> y >> z;

	return vec3(x, y, z);
}
vec4 FileCFG::getVec4(string key) {
	string data = get(key);
	if (!data.length())
		return vec4();

	stringstream geek(data);
	float x, y, z, w;
	geek >> x >> y >> z >> w;

	return vec4(x, y, z, w);
}

void FileCFG::load(string filename) {
	ifstream fCFG;
	fCFG.open(filename.c_str(), ios::in);
	if (!fCFG.is_open())
		throw error("LOAD_FAIL", "Can't read file: " + filename);

	string line;
	vector<string> sessionKey, sessionValue;
	short session = 0;

	while (!fCFG.eof()) {
		getline(fCFG, line);
		if (line.length() == 0 || line[0] == ';')
			continue;

		if (line[0] == '[') { // session
			if (session) {
				m_key.push_back(sessionKey);
				m_value.push_back(sessionValue);
				sessionKey.clear();
				sessionValue.clear();
			}

			m_sessions.push_back(line.substr(1, line.length() - 2));
			session++;
		}
		else {
			int pos = line.find("=");
			if (pos >= 0) {
				sessionKey.push_back(line.substr(0, pos));
				sessionValue.push_back(line.substr(pos+1, line.length()-pos-1));
			}
			else {
				sessionValue.push_back(line);
			}
		}
	}
	if (session) {
		m_key.push_back(sessionKey);
		m_value.push_back(sessionValue);
		sessionKey.clear();
		sessionValue.clear();
	}
	fCFG.close();
}
