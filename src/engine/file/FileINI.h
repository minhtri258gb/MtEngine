#ifndef __MT_FILE_INI_H__
#define __MT_FILE_INI_H__

namespace mt {

class FileINI {

public:

	// Forward
	FileINI();
	FileINI(std::string filepath);
	~FileINI();
	void load(std::string filepath);

	// Native
	void save(std::string filepath);
	std::string get(std::string session, std::string key);
	void set(std::string session, std::string key, std::string value);

	// Stock

private:

	// Variable
	class FileINIImpl;
	FileINIImpl* impl;

};

}

#endif
