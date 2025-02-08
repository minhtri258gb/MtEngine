#define __MT_SCREEN_CPP__

#include "common.h"
#include "engine/Log.h"
#include "graphic/Graphic.h"
#include "Screen.h"

#include "hud/HudFpsCount.h"
#include "ui/PanelConsole.h"
#include "ui/PanelMenu.h"
#include "ui/PanelHelp.h"
#include "ui/PanelSetting.h"
#include "ui/PanelMonitor.h"

using namespace std;
using namespace mt::engine;
using namespace mt::graphic;
using namespace mt::game;


class Screen::ScreenImpl {
public:

	// Variable
	map<string, Hud*> mapHud;
	map<string, Panel*> mapPanel;
};

Screen::Screen() {

	// Implement
	this->impl = new ScreenImpl();
}
Screen::~Screen() {

	// Implement
	delete this->impl;
}

void Screen::init() {
	LOG("init");
	try {

		// Hud
		this->add("FPS", new HudFpsCount());

		// Panel
		this->add("console", new PanelConsole());
		this->add("menu", new PanelMenu());
		this->add("help", new PanelHelp());
		this->add("setting", new PanelSetting());
		this->add("monitor", new PanelMonitor());
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}
void Screen::update() {
	LOG("update");
	try {

		for(pair<string, Hud*> it : impl->mapHud) {
			Hud* hud = it.second;
			if (!hud->isActive)
				continue;

			hud->update();
		}
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}
void Screen::close() {
	LOG("close");
	try {

		// Text
		for(pair<string, Hud*> it : impl->mapHud) {
			Hud* hud = it.second;
			delete hud;
		}
		impl->mapHud.clear();

		// Panel
		for(pair<string, Panel*> it : impl->mapPanel) {
			Panel* panel = it.second;
			delete panel;
		}
		impl->mapPanel.clear();
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}

Hud* Screen::getHud(std:: string name) {
	if (impl->mapHud.find(name) != impl->mapHud.end())
		return impl->mapHud.at(name);
	return nullptr;
}
void Screen::add(string _name, Hud* _hud) {
	LOG("add - HUD");
	try {
		impl->mapHud.insert({_name, _hud});
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}

Panel* Screen::getPanel(std:: string name) {
	if (impl->mapPanel.find(name) != impl->mapPanel.end())
		return impl->mapPanel.at(name);
	return nullptr;
}
bool Screen::togglePanel(std:: string name) {
	LOG("togglePanel");
	try {

		Panel* pPanel = this->getPanel(name);
		if (pPanel == nullptr)
			throw error("PANEL_NOT_FOUND", "Không tìm thấy Panel: "+name);

		// Toggle Show Panel
		bool isShow = !pPanel->isShow();
		pPanel->show(isShow);
		return isShow;
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}
void Screen::add(string _name, Panel* _panel) {
	LOG("add - Panel");
	try {
		impl->mapPanel.insert({_name, _panel}); // Thêm vào map để quản lý
		Graphic::ins.gui.add(_panel); // Thêm vào GUI của Graphic để render
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}
