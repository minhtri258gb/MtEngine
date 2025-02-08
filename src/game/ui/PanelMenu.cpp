#define __MT_PANEL_MENU_CPP__

#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>

#include "common.h"
// #include "engine/Config.h"
#include "engine/Log.h"
#include "engine/Timer.h"
// #include "graphic/Graphic.h"
#include "game/Game.h"
#include "PanelMenu.h"

using namespace std;
using namespace mt;
using namespace mt::engine;
using namespace mt::graphic;
using namespace mt::game;


PanelMenu::PanelMenu() {
	// this->m_show = true;
}

PanelMenu::~PanelMenu() {
}

void PanelMenu::render() {
	LOG("render");
	try {

		if (!this->m_show)
			return;

		ImGui::Begin("Menu", &this->m_show); // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
		ImGui::Text("Hello from another window!");
		if (ImGui::Button("Close Me"))
			this->m_show = false;

		// Exit
		if (ImGui::Button("Exit"))
			Game::ins.exit();

		ImGui::End();
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}
