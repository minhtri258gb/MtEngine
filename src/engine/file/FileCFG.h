#ifndef __MT_FILE_CFG_H__
#define __MT_FILE_CFG_H__

namespace mt {

class FileCFG
{
public:

	// Constructor
	FileCFG();
	FileCFG(std::string);
	~FileCFG();

	void select(std::string session);
	void addSession(std::string key);
	void set(std::string key, std::string value);
	void save(std::string filepath);
	std::vector<std::string> keys();
	std::vector<std::string> values();

	std::string get(std::string key);
	bool getBool(std::string key);
	int getInt(std::string key);
	uint getUInt(std::string key);
	float getFloat(std::string key);
	vec2 getVec2(std::string key);
	vec3 getVec3(std::string key);
	vec4 getVec4(std::string key);


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
