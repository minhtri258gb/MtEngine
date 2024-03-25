#ifndef __TEXTURE_ATLAS_H__
#define __TEXTURE_ATLAS_H__

namespace mt {
namespace graphic {

class TextureAtlas
{
public:

	// Constructor
	TextureAtlas();
	~TextureAtlas();

	// General
	void init(std::string filepath, int column, int row);
	void bind();

	// Get
	int getColumn();
	int getRow();
	void getCoordOffset(int index, float &u, float &v);
	void getSizeTile(float &u, float &v);

private:

	// Variable
	unsigned int gl_textureId;
	int column;
	int row;
};

}}

#endif
