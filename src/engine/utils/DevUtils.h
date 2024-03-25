#ifndef __MT_DEV_UTILS_H__
#define __MT_DEV_UTILS_H__

namespace mt {
namespace engine {

class DevUtils {

public:

  // GLM convert
  static mat4 glm2mt(glm::mat4);
  static glm::mat4 mt2glm(mat4);
  static vec4 glm2mt(glm::vec4);
  static glm::vec4 mt2glm(vec4);
  static vec3 glm2mt(glm::vec3);
  static glm::vec3 mt2glm(vec3);

};

}}

#endif
