#define __MT_PANEL_CPP__

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <ft2build.h>
#include <freetype/freetype.h>

#include "common.h"
#include "engine/Config.h"
#include "graphic/Graphic.h"
#include "Panel.h"

using namespace std;
using namespace mt;
using namespace mt::engine;
using namespace mt::graphic;


Panel::Panel() {
	this->m_show = false;
}

Panel::~Panel() {
}

void Panel::render() {
	std::cout << "\033[0;31mERROR\033[0m: " << __FILE__ << ", " << __LINE__ << std::endl;
}

bool Panel::isShow() {
	return this->m_show;
}
void Panel::show(bool toggle) {
	this->m_show = toggle;
}