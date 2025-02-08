#define __MT_GUI_CPP__

#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>

#include "common.h"
#include "engine/Config.h"
#include "engine/Log.h"
#include "engine/Timer.h"
#include "GUI.h"
#include "Graphic.h"

using namespace std;
using namespace mt;
using namespace mt::engine;
using namespace mt::graphic;


class Graphic::GraphicImpl {
public:
	GLFWwindow* gl_window;
};

class GUI::GUIImpl {
public:
	bool m_showCursor;
};

GUI::GUI() {
	LOG("GUI");
	try {

		// Implement
		impl = new GUIImpl();
		impl->m_showCursor = false;
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}

GUI::~GUI() {

	// Implement
	delete impl;
}

void GUI::init() {
	LOG("init");
	try {

		// ImGUI Init
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		// ImGui::StyleColorsLight();

		// Setup Platform/Renderer backends
		ImGui_ImplGlfw_InitForOpenGL(Graphic::ins.impl->gl_window, true);
		ImGui_ImplOpenGL3_Init("#version 130"); // #TODO

		// Load Fonts
		io.Fonts->AddFontFromFileTTF("./res/fonts/Alata-Regular.ttf", 16.0f);
		io.Fonts->AddFontFromFileTTF("./res/fonts/BeVietnam-Medium.ttf", 16.0f);

		// UI Shader
		float width = Config::ins.windowWidth;
		float height = Config::ins.windowHeight;

		this->proj.ortho(0.0f, (float)width, 0.0f, (float)height); // , 0.0f, 10.0f

		Graphic::ins.shaderProgramMgr.setScreenProj(proj);

		// Init component
		Text::initText();
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}

void GUI::update() {
	LOG("update");
	try {
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}

void GUI::render() {
	LOG("render");
	try {

		// Render HUD
		for (uint i=0, sz=this->lstText.size(); i<sz; i++)
			this->lstText.at(i)->render();

		// Prepare ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// Render ImGUI
		for (uint i=0, sz=this->lstPanel.size(); i<sz; i++)
			this->lstPanel.at(i)->render();

		// Final Render ImGUI
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}

void GUI::close() {
	LOG("close");
	try {

		// Cleanup
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}

void GUI::add(Text* text) {
	LOG("add: Text");
	try {
		this->lstText.push_back(text);
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}

void GUI::add(Panel* panel) {
	LOG("add: Panel");
	try {
		this->lstPanel.push_back(panel);
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}
