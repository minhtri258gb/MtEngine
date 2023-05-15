#ifndef __CFGFILE_H__
#define __CFGFILE_H__

class CFGFile
{
public:

	// Constructor / Destructor
	CFGFile(string);
	~CFGFile();

	// Get / Set
	void select(string);
	string get(string);
	bool getBool(string);
	int getInt(string);
	float getFloat(string);
	vec3 getVec3(string);

private:

	// Variable
	vector<string> m_sessions;
	vector<vector<string>> m_key;
	vector<vector<string>> m_value;
	short sessionID;

	// Change data
	void load(string);
};

#endif