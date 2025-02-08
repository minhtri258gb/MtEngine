#define __MT_PANEL_HELP_CPP__

#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>

#include "common.h"
// #include "engine/Config.h"
#include "engine/Log.h"
#include "engine/Timer.h"
// #include "graphic/Graphic.h"
#include "PanelHelp.h"

using namespace std;
using namespace mt;
using namespace mt::engine;
using namespace mt::graphic;
using namespace mt::game;


PanelHelp::PanelHelp() {
}

PanelHelp::~PanelHelp() {
}

void PanelHelp::render() {
	LOG("render");
	try {

		if (!this->m_show)
			return;

		ImGui::ShowDemoWindow(&this->m_show);
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}
