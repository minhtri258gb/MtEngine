#define __MT_GRAPHIC_CPP__

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "common.h"
#include "engine/Config.h"
#include "engine/Log.h"
#include "engine/Input.h"
#include "Graphic.h"

using namespace std;
using namespace mt;
using namespace mt::engine;
using namespace mt::graphic;


Graphic Graphic::ins;

class Graphic::GraphicImpl {
public:
	GLFWwindow* gl_window;

	// Cursor
	bool m_showCursor;
	vec2 m_center;
};

void cbk_framebuffer_size(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}
void cbk_cursor_pos(GLFWwindow *window, double xpos, double ypos) {
	if (!Graphic::ins.isShowCursor())
		Input::ins.cursorPos(xpos, ypos, false);
}
void cbk_key(GLFWwindow *window, int key, int scancode, int action, int mods) {
	if (key == -1)
		return;
	if (action == GLFW_PRESS)
		Input::ins.keyPress(key, true);
	else if (action == GLFW_RELEASE)
		Input::ins.keyPress(key, false);
}
void cbk_mouse_button(GLFWwindow *window, int button, int action, int mods) {
	bool press;
	switch (action) {
		case GLFW_PRESS:
			press = true;
			break;
		case GLFW_RELEASE:
			press = false;
			break;
		default:
			return;
	}

	if (button > 2)
		return;

	Input::ins.keyPress(351 + button, press);
}

Graphic::Graphic() {
	// Impliment
	impl = new GraphicImpl();
	impl->m_showCursor = true;
}
Graphic::~Graphic() {
	// Impliment
	delete impl;
}

void Graphic::init() {
	try {

		// Data
		int width = Config::ins.windowWidth;
		int height = Config::ins.windowHeight;
		string name = Config::ins.windowName;

		// Set
		impl->m_center = vec2(width/2, height/2);

		// Init OpenGL
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		//glfwWindowHint(GLFW_SAMPLES, 4);

		impl->gl_window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
		// impl->gl_window = glfwCreateWindow(width, height, name.c_str(), glfwGetPrimaryMonitor(), NULL);
		if (impl->gl_window == NULL) {
			glfwTerminate();
			throw error("GLFW_INIT_FAIL", "Failed to create GLFW window");
		}
		glfwMakeContextCurrent(impl->gl_window);

		// VSync
		if (Config::ins.graphic_vsync)
			glfwSwapInterval(1); // Enable vsync

		// Set icon
		// GLFWimage icons[2];
		// icons[0].pixels = stbi_load("res/system/logo.ico", &icons[0].width, &icons[0].height, 0, 4);
		// if(icons[0].pixels) {
		// 	icons[1] = icons[0];
		// 	glfwSetWindowIcon(window, 2, icons);
		// }

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			throw error("GLAD_INIT_FAIL", "Failed to initialize GLAD");

		glViewport(0, 0, width, height);

		glfwSetFramebufferSizeCallback(impl->gl_window, cbk_framebuffer_size);
		glfwSetCursorPosCallback(impl->gl_window, cbk_cursor_pos);
		glfwSetKeyCallback(impl->gl_window, cbk_key);
		glfwSetMouseButtonCallback(impl->gl_window, cbk_mouse_button);

		glfwSetInputMode(impl->gl_window, GLFW_STICKY_KEYS, GLFW_TRUE);

		// Set default
		this->showCursor(false);
		this->cullFaceToogle(true);
		this->cullFaceBack(true);
		this->cullFaceClock(true);
		this->setDepthTest();
		// glEnable(GL_MULTISAMPLE);

		// Init component
		this->shaderProgramMgr.init();

		// Init Scene
		this->scene.init();

		// Init GUI
		this->gui.init();

		// Init Model
		this->modelMgr.init();

		// #EXTRA
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}
void Graphic::update() {
	this->scene.update();
	this->gui.update();
}
void Graphic::render() {
	// Bật buffer Đổ bóng
	// Render bóng
	// Tắt buffer Đổ bóng

	// Bật buffer phản chiếu
	// Render cảnh ngược
	// Tắt buffer phản chiếu

	// Bật buffer cảnh
	this->scene.render();
	// Tắt buffer cảnh

	// Render màn hình cảnh

	// Render GUI
	this->gui.render();
}
void Graphic::close() {
	LOG("close");
	try {

		// Clear
		this->modelMgr.clear();

		// Close component
		this->shaderProgramMgr.close();

		// #EXTRA

		// Close GLFW
		glfwTerminate();
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}

void Graphic::addModel(Model* model, vec3* pos, quat* rot, vec3* scale) {
	this->scene.lstModel.push_back(ModelRender(model, pos, rot, scale));
}

// void Graphic::processInput() {
// 	if (glfwGetKey(impl->gl_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
// 		glfwSetWindowShouldClose(impl->gl_window, true);
// }

void Graphic::renderPre() {
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void Graphic::renderPost() {
	Input::ins.resetStatus(); // end frame key press
	glfwPollEvents(); // start frame key press
	glfwSwapBuffers(impl->gl_window);
}

bool Graphic::checkWindow() {
	return !glfwWindowShouldClose(impl->gl_window);
}

double Graphic::getTime() {
	return glfwGetTime();
}

bool Graphic::isShowCursor() {
	LOG("isShowCursor");
	try {
		return impl->m_showCursor;
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}
void Graphic::showCursor(bool toogle) {
	LOG("showCursor");
	try {

		if (toogle == impl->m_showCursor)
			return;

		// Set cursor state
		glfwSetInputMode(impl->gl_window, GLFW_CURSOR, toogle ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);

		glfwSetCursorPos(impl->gl_window, impl->m_center.x, impl->m_center.y);
		Input::ins.cursorPos(impl->m_center.x, impl->m_center.y, true);

		// Save state
		impl->m_showCursor = toogle;
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}

void Graphic::cullFaceToogle(bool _value) {
	if (_value)
		glEnable(GL_CULL_FACE);
	else
		glDisable(GL_CULL_FACE);
}
void Graphic::cullFaceBack(bool _value) {
	if (_value)
		glCullFace(GL_BACK);
	else
		glCullFace(GL_FRONT);
}
void Graphic::cullFaceClock(bool _value) {
	if (_value)
		glFrontFace(GL_CCW);
	else
		glFrontFace(GL_CW);
}

void Graphic::setDepthTest(bool _value) {
	if (_value)
		glEnable(GL_DEPTH_TEST);
	else
		glDisable(GL_DEPTH_TEST);
}

void Graphic::wireframe(bool _value) {
	if (_value)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Graphic::blendToogle(bool _value) {
	if (_value)
		glEnable(GL_BLEND);
	else
		glDisable(GL_BLEND);
}
void Graphic::blendFunc(int value) {
	switch (value) {
		case 1: glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); break;
		case 2: glBlendFunc(GL_SRC_ALPHA, GL_ONE); break;
		default: break;
	}
}

int Graphic::getPatchParameterMax() {
	GLint MaxPatchVertices = 0;
	glGetIntegerv(GL_MAX_PATCH_VERTICES, &MaxPatchVertices);
	return MaxPatchVertices;
}
void Graphic::setPatchParameter(int value) {
	glPatchParameteri(GL_PATCH_VERTICES, value);
}

void Graphic::setDepthMark(bool toogle) {
	if (toogle) glDepthMask(GL_TRUE);
	else glDepthMask(GL_FALSE);
}