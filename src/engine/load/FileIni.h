#ifndef __MT_FILE_INI_H__
#define __MT_FILE_INI_H__

namespace mt {
namespace engine {

class FileIni {

public:

	// Forward
	FileIni();
	FileIni(std::string filepath);
	~FileIni();
	void load(std::string filepath);

	// Native
	void save(std::string filepath);
	std::string get(std::string session, std::string key);
	void set(std::string session, std::string key, std::string value);

	// Stock

private:

	// Variable
	class FileIniImpl;
	FileIniImpl* impl;

};

}}

#endif
