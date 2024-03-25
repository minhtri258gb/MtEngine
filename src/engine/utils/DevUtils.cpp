#define __MT_DEV_UTILS_CPP__

#include <stdarg.h>
#include <sstream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "common.h"
#include "DevUtils.h"

using namespace std;
using namespace mt;
using namespace mt::engine;

mat4 DevUtils::glm2mt(glm::mat4 m)
{
  return mat4(
    m[0][0], m[0][1], m[0][2], m[0][3],
    m[1][0], m[1][1], m[1][2], m[1][3],
    m[2][0], m[2][1], m[2][2], m[2][3],
    m[3][0], m[3][1], m[3][2], m[3][3]
  );
}

glm::mat4 DevUtils::mt2glm(mat4 m)
{
  glm::mat4 res = glm::mat4(1);
  for (int i=0; i<4; i++)
  for (int j=0; j<4; j++)
    res[i][j] = m[i*4+j];
  return res;
}

vec4 DevUtils::glm2mt(glm::vec4 v)
{
  return vec4(v.x, v.y, v.z, v.w);
}

glm::vec4 DevUtils::mt2glm(vec4 v)
{
  return glm::vec4(v.x, v.y, v.z, v.w);
}

vec3 DevUtils::glm2mt(glm::vec3 v)
{
  return vec3(v.x, v.y, v.z);
}

glm::vec3 DevUtils::mt2glm(vec3 v)
{
  return glm::vec3(v.x, v.y, v.z);
}
