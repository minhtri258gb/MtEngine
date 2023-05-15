#ifndef __MT_FILE_JSON_H__
#define __MT_FILE_JSON_H__

namespace mt {
namespace test {

class JsonNode
{
public:

};

class FileJson {

public:

	// Forward
	FileJson();
	FileJson(std::string filepath);
	~FileJson();
	void load(std::string filepath);
	void run();

	// Native
	void save(std::string filepath);
	std::string get(std::string key);
	int getInt(std::string key);
	float getFloat(std::string key);
	bool getBool(std::string key);
	JsonNode getNode(std::string key);
	std::vector<JsonNode> getList(std::string key);
	void set(std::string key, std::string value);
	void set(std::string key, int value);
	void setFloat(std::string key);
	void setBool(std::string key);
	void setNode(std::string key);
	void setList(std::string key);

	// Stock

private:

	// Variable
	class FileJsonImpl;
	FileJsonImpl* impl;

};

}}

#endif
