#ifndef __MT_FRAME_BUFFER_H__
#define __MT_FRAME_BUFFER_H__

namespace mt {
namespace graphic {

class FrameBuffer
{
public:

	// Forwards
	FrameBuffer();
	~FrameBuffer();

	void init(int width, int height);
	void initTextureAttachment();
	void initDepthTextureAttachment();
	void initDepthBufferAttachment();
	void initRenderBufferAttachment();

	void bindFrameBuffer();
	void bindTextureColor();
	void bindTextureDepth();
	void bindRenderBuffer();
	void bindDepthBuffer();
	void unbindFrameBuffer();
	void unbindTextureColor();
	void unbindTextureDepth();
	void unbindRenderBuffer();
	void unbindDepthBuffer();

	// Natives
	// bool point(vec3 pos);
	// bool sphere(vec3 pos, float radius);
	// bool AABB(vec3 pos, float size);

private:

	// Variable
	int width, height;
	unsigned int gl_frameBuffer;
	unsigned int gl_textureColor;
	unsigned int gl_textureDepth;
	unsigned int gl_depthBuffer;
	unsigned int gl_renderBuffer;
};

}}

#endif
