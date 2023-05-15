#ifndef __MT_SCREEN_H__
#define __MT_SCREEN_H__

namespace mt {
namespace graphic {

class Screen
{

public:

	// Variable
	mat4 proj;
	mat4 view;

	// Forward
	Screen();
	~Screen();
	void init();

	// Native

};

}}

#endif
