#ifndef __MT_FONT_H__
#define __MT_FONT_H__

#include "../ShaderProgram.h"

namespace mt {
namespace graphic {

class Font {
public:

	// Variables
	static ShaderProgram shader;
	// VertexBufferDynamic m_vb;
	// float m_maxwidth, m_maxlength;

	// Forwards
	Font();
	~Font();

	void init();
	void render();

	// Natives

private:

	// Variable
	class FontImpl;
	FontImpl* impl;
	// Texture2DPack m_texture;
	// vector<float> heightmap, heightmapPhysic;

};

}}

#endif
