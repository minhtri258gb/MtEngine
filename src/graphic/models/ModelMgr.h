#ifndef __MT_MODEL_MANAGER_H__
#define __MT_MODEL_MANAGER_H__

#include "ModelBuilder.h"
#include "Model.h"

namespace mt {
namespace graphic {

class ModelMgr
{

public:

	// Variable

	// Forward
	ModelMgr();
	~ModelMgr();
	void init();
	void clear();

	// Native
	Model* cache(std::string name);

private:

	// Variable
	ModelBuilder builder;
	std::map<std::string, Model*> models;

	// Natives
	Model* getModel(std::string name);
	void addModel(std::string name, Model*);

};

}}

#endif
