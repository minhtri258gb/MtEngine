#ifndef __MT_TEXTURE_CUBE_H__
#define __MT_TEXTURE_CUBE_H__

namespace mt {
namespace graphic {

class TextureCube
{
public:

	// Forwards
	TextureCube();
	~TextureCube();
	void init(std::string filepath, bool flip = false);
	
	// Native
	void bind(unsigned int location = 0);

private:

	// Variables
	unsigned int gl_textureId;

};

}}

#endif
