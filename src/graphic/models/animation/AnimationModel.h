#ifndef __MT_ANIMATION_MODEL_H__
#define	__MT_ANIMATION_MODEL_H__

#include "../../ShaderProgram.h"
// #include "../ModelBuilder.h"

namespace mt {
namespace graphic {

class AnimationModel
{
public:

    // Variable
	static ShaderProgram shader;
	// friend class ModelBuilder;

    // Forwards
    AnimationModel();
    ~AnimationModel();
    // bool init(const std::string& filename);
    void update();
    void render();

private:

    // Variable
    class AnimationModelImpl;
    AnimationModelImpl* impl;
    
};

}}

#endif
