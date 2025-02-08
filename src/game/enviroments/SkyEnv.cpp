#define __MT_SKY_ENV_CPP__

#include "common.h"
#include "engine/Config.h"
#include "engine/Log.h"
#include "engine/file/FileCFG.h"
#include "engine/file/Image.h"
#include "graphic/Graphic.h"
#include "SkyEnv.h"

#include "graphic/sky/SkyBox.h"

using namespace std;
using namespace mt::engine;
using namespace mt::graphic;
using namespace mt::game;


class SkyEnv::SkyEnvImpl {
public:
	SkyBox* model;
	string m_name;
};

SkyEnv::SkyEnv(string name) {
	LOG("SkyEnv");
	try {

		// Data
		FileCFG fCFG(Config::ins.skybox_path + name + "/info.cfg");

		// Implement
		impl = new SkyEnvImpl();
		impl->m_name = name;
		
		// Load config
		// #TODO

		// Init Model
		impl->model = new SkyBox();
		impl->model->init(name);
		Graphic::ins.scene.sky = impl->model;
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}
SkyEnv::~SkyEnv() {
	LOG("~SkyEnv");

	// ~Model
	if (impl->model) {
		impl->model->clear();
		delete impl->model;
		impl->model = nullptr;
		Graphic::ins.scene.sky = nullptr;
	}

	// ~Implement
	delete impl;
}

void SkyEnv::update() {
	LOG("update");
	try {

		// Update physic location
		// impl->body->getTransForm(&this->pos, &this->rot);

		// cout << this->pos.y << endl;
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}
