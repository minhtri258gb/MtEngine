#ifndef __MT_LOG_H__
#define __MT_LOG_H__

namespace mt {
namespace engine {

class Log {
public:

	// Variables
	static Log ins;

	// Constructor
	Log();
	~Log();

	// Method
	void l(std::string file, int line, std::string message);
};

}}

#endif
