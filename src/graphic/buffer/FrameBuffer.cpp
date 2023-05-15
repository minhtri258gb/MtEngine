#define __MT_FRAME_BUFFER_CPP__

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "common.h"
#include "engine/Config.h"
#include "../Graphic.h"
#include "FrameBuffer.h"

using namespace std;
using namespace mt;
using namespace mt::engine;
using namespace mt::graphic;

FrameBuffer::FrameBuffer()
{
	width = Config::ins.windowWidth;
	height = Config::ins.windowHeight;
	gl_frameBuffer = 0;
	gl_textureColor = 0;
	gl_textureDepth = 0;
	gl_depthBuffer = 0;
	gl_renderBuffer = 0;
}

FrameBuffer::~FrameBuffer()
{
	if (gl_frameBuffer)
		glDeleteFramebuffers(1, &gl_frameBuffer);
	if (gl_textureColor)
		glDeleteTextures(1, &gl_textureColor);
	if (gl_textureDepth)
		glDeleteTextures(1, &gl_textureDepth);
	if (gl_depthBuffer)
		glDeleteRenderbuffers(1, &gl_depthBuffer);
	if (gl_renderBuffer)
		glDeleteRenderbuffers(1, &gl_renderBuffer);
}

void FrameBuffer::init(int width, int height)
{
	// set value
	this->width = width;
	this->height = height;

	// main
	glGenFramebuffers(1, &gl_frameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, gl_frameBuffer);
	glDrawBuffer(GL_COLOR_ATTACHMENT0);
}

void FrameBuffer::initTextureAttachment()
{
	glGenTextures(1, &gl_textureColor);
	glBindTexture(GL_TEXTURE_2D, gl_textureColor);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, gl_textureColor, 0);
}

void FrameBuffer::initDepthTextureAttachment()
{
	glGenTextures(1, &gl_textureDepth);
	glBindTexture(GL_TEXTURE_2D, gl_textureDepth);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, gl_textureDepth, 0);
}

void FrameBuffer::initDepthBufferAttachment()
{
	glGenRenderbuffers(1, &gl_depthBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, gl_depthBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, gl_depthBuffer);
}

void FrameBuffer::initRenderBufferAttachment()
{
	glGenRenderbuffers(1, &gl_renderBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, gl_renderBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height); // use a single renderbuffer object for both a depth AND stencil buffer.
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, gl_renderBuffer); // now actually attach it
}

void FrameBuffer::bindFrameBuffer()
{
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, gl_frameBuffer);
	glViewport(0, 0, width, height);
}

void FrameBuffer::unbindFrameBuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, Config::ins.windowWidth, Config::ins.windowHeight);
}
