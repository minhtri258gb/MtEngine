#ifndef __MT_TEXT_H__
#define __MT_TEXT_H__

#include "../ShaderProgram.h"

namespace mt {
namespace graphic {

class Text
{
public:

	// Variables
	static ShaderProgram shader;

	// Static method
	static void initText();
	
	// Forwards
	Text();
	~Text();

	void init(std::string content, vec2 position, float scale, vec3 color);
	void close();
	void render();

	// Natives
	void setContent(std::string);

private:

	// Variable
	class TextImpl;
	TextImpl* impl;

};

}}

#endif
