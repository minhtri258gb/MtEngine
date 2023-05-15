#define __MT_FILE_INI_CPP__

#include <mini/ini.h>

#include "common.h"
#include "FileIni.h"

using namespace std;
using namespace mINI;
using namespace mt::engine;

class FileIni::FileIniImpl
{
public:
	INIStructure ini;
};

FileIni::FileIni()
{
	this->impl = new FileIniImpl();
}

FileIni::FileIni(string filepath)
{
	this->impl = new FileIniImpl();
	this->load(filepath);
}

FileIni::~FileIni()
{
	delete this->impl;
}

void FileIni::load(string filepath)
{
	INIFile file(filepath);
	file.read(this->impl->ini);
}

void FileIni::save(string filepath)
{
	INIFile file(filepath);
	file.write(this->impl->ini);
}

string FileIni::get(string session, string key)
{
	return this->impl->ini[session][key];
}

void FileIni::set(string session, string key, string value)
{
	this->impl->ini[session][key] = value;
}
