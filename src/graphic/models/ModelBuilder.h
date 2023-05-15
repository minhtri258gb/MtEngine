#ifndef __MT_MODEL_BUILDER_H__
#define __MT_MODEL_BUILDER_H__

#include "Model.h"

namespace mt {
namespace graphic {

class ModelBuilder
{

public:

	// Forwards
	ModelBuilder();
	~ModelBuilder();

	// Native
	Model* loadModel(std::string name);
	Model* createDefaultModel(std::string name);
	Model* createBox();
	Model* createPlane();

private:

	// Variables
	class ModelBuilderImpl;
	ModelBuilderImpl* impl;

};

}}

#endif
