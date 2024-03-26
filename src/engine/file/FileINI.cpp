#define __MT_FILE_INI_CPP__

#include <mini/ini.h>

#include "common.h"
#include "FileINI.h"

using namespace std;
using namespace mINI;
using namespace mt;

class FileINI::FileINIImpl
{
public:
	INIStructure ini;
};

FileINI::FileINI()
{
	this->impl = new FileINIImpl();
}

FileINI::FileINI(string filepath)
{
	this->impl = new FileINIImpl();
	this->load(filepath);
}

FileINI::~FileINI()
{
	delete this->impl;
}

void FileINI::load(string filepath)
{
	INIFile file(filepath);
	file.read(this->impl->ini);
}

void FileINI::save(string filepath)
{
	INIFile file(filepath);
	file.write(this->impl->ini);
}

string FileINI::get(string session, string key)
{
	return this->impl->ini[session][key];
}

void FileINI::set(string session, string key, string value)
{
	this->impl->ini[session][key] = value;
}
