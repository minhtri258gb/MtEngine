#define __MT_MODEL_MANAGER_CPP__

#include "common.h"
#include "engine/Log.h"
#include "ModelMgr.h"

#include "ModelBuilder.h"
#include "SimpleModel.h"

using namespace std;
using namespace mt::engine;
using namespace mt::graphic;


ModelMgr::ModelMgr() {
	LOG("ModelMgr");
}
ModelMgr::~ModelMgr() {
	LOG("~ModelMgr");
}

void ModelMgr::init() {
	LOG("~init");
}
void ModelMgr::clear() {
	LOG("clear");
	try {

		// Clear Model
		map<string, Model*>::iterator it;
		for (it = this->models.begin(); it != this->models.end(); it++)
			delete it->second;
		this->models.clear();
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}

Model* ModelMgr::cache(string name) {
	LOG("cache");
	try {

		// Get available model
		Model* model = this->getModel(name);
		if (!model)
		{
			model = this->builder.loadModel(name);
			this->addModel(name, model);
		}
		return model;
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}
Model* ModelMgr::getModel(string name) {
	LOG("getModel");
	try {
		if (this->models.count(name) == 1)
			return this->models.at(name);
		return nullptr;
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}
void ModelMgr::addModel(string name, Model* model) {
	this->models.emplace(name, model);
}
