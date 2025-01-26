#ifndef __MT_EXCEPTION_H__
#define __MT_EXCEPTION_H__

#define error(code, msg) Exception(code, msg,__FILE__,__LINE__)
#define warning(code, msg) Exception(code, msg,__FILE__,__LINE__)
#define track(e) e.addTrack(__FILE__,__LINE__)

namespace mt {

class Exception {

public:

	// Forward
	Exception();
	Exception(std::string code, std::string msg, std::string file, int line);
	~Exception();

	// Native
	std::string getCode();
	std::string getMessage();
	void setMessage(std::string code, std::string msg, std::string file, int line);
	void addTrack(std::string file, int line);

	// Stock

protected:

	// Variable
	std::string code;
	std::string message;
	std::vector<std::string> files;
	std::vector<int> lines;

};

}

#endif
