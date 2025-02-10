#ifndef __MT_TEXTURE_H__
#define __MT_TEXTURE_H__

namespace mt {
namespace graphic {

class Texture {

public:

	// Constructor
	Texture();
	~Texture();

	// General
	void loadImage(std::string filepath, bool flip = false);
	void loadArray(float* pData, int width, int height);
	void bind(unsigned int location = 0);

private:

	// Variables
	unsigned int gl_textureId;
};

}}

#endif
