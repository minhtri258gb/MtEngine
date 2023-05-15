#ifndef __MT_EXCEPTION_H__
#define __MT_EXCEPTION_H__

#define error(msg) Exception(msg,__FILE__,__LINE__)
#define warning(msg) Exception(msg,__FILE__,__LINE__)

namespace mt {

class Exception {

public:

	// Forward
	Exception();
	Exception(std::string msg, std::string file, int line);
	~Exception();

	// Native
	std::string getMessage();
	void setMessage(std::string msg, std::string file, int line);

	// Stock

protected:

	// Variable
	std::string message;
	std::string file;
	int line;

};

}

#endif
