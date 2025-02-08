#define __MT_PANEL_MONITOR_CPP__

#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>

#include "common.h"
// #include "engine/Config.h"
#include "engine/Log.h"
#include "engine/Timer.h"
// #include "graphic/Graphic.h"
#include "game/Game.h"
#include "PanelMonitor.h"

using namespace std;
using namespace mt;
using namespace mt::engine;
using namespace mt::graphic;
using namespace mt::game;


PanelMonitor::PanelMonitor() {
	this->m_show = false;
	this->m_fps = true;
	this->m_origin = false;
}

PanelMonitor::~PanelMonitor() {
}

void PanelMonitor::render() {
	LOG("render");
	try {

		if (!this->m_show)
			return;


		ImGui::Begin("Monitor", &this->m_show); // Create a window called "Hello, world!" and append into it.

		// FPS
		ImGui::Checkbox("FPS", &this->m_fps);
		if (this->m_fps) {
			ImGui::SameLine();
			int fps = Timer::ins.getFPS();
			ImGui::Text("%d", fps);
		}

		// Origin
		ImGui::Checkbox("Origin", &this->m_origin);
		if (this->m_origin) {
			ImGui::SameLine();
			vec3 origin = Game::ins.map->player.origin;
			ImGui::Text("%.2f, %.2f, %.2f", origin.x, origin.y, origin.z);
		}

		static float f = 0.0f;
		ImGui::SliderFloat("float", &f, 0.0f, 1.0f); // Edit 1 float using a slider from 0.0f to 1.0f

		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
		ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

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
