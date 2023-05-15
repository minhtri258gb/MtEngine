#ifndef __MT_TEXT_FILE_H__
#define __MT_TEXT_FILE_H__

#include <fstream>

namespace mt {
namespace engine {

class TextFile {

public:

	// Variable
	std::ifstream file;

	// Forward
	TextFile(std::string filename);
	~TextFile();

	// Native
	long getLength();
	void read(char* buffer, long length);

	// Stock

};

}}

#endif
