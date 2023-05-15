#ifndef __MT_FILE_CFG_H__
#define __MT_FILE_CFG_H__

namespace mt {

class FileCFG
{
public:

	// Constructor
	FileCFG(std::string);
	~FileCFG();

	// Get / Set
	void select(std::string);
	std::string get(std::string);
	bool getBool(std::string);
	int getInt(std::string);
	uint getUInt(std::string);
	float getFloat(std::string);
	vec3 getVec3(std::string);
	std::map<std::string, std::string>* getPtr();

private:

	// Variable
	std::vector<std::string> m_sessions;
	std::vector<std::vector<std::string>> m_key;
	std::vector<std::vector<std::string>> m_value;
	short sessionID;

	// Change data
	void load(std::string);
};

}

#endif
