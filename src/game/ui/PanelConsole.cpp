#define __MT_PANEL_CONSOLE_CPP__

#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>

#include "common.h"
// #include "engine/Config.h"
#include "engine/Log.h"
#include "engine/Timer.h"
// #include "graphic/Graphic.h"
#include "PanelConsole.h"

using namespace std;
using namespace mt;
using namespace mt::engine;
using namespace mt::graphic;
using namespace mt::game;


PanelConsole::PanelConsole() {
}

PanelConsole::~PanelConsole() {
}

void PanelConsole::render() {
	LOG("render");
	try {

		if (!this->m_show)
			return;

		static float f = 0.0f;
		static int counter = 0;
		bool show_demo_window = true;
		bool show_another_window = false;
		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

		ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

		ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
		ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
		ImGui::Checkbox("Another Window", &show_another_window);

		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
		ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

		if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
			counter++;
		ImGui::SameLine();
		ImGui::Text("counter = %d", counter);

		ImGui::Text("FPS: %d", Timer::ins.getFPS());
		ImGui::End();
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}
