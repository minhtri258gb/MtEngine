#ifndef __MT_COMMON_H__
#define __MT_COMMON_H__

#if 1
#define LOG(msg) Log::ins.l(__FILE__, __LINE__, msg)
#else
#define LOG ;
#endif

#include <iostream>
#include <vector>
#include <map>

// #include <glm/glm.hpp>
// #include <glm/gtc/matrix_transform.hpp>
// #include <glm/gtc/type_ptr.hpp>

#include "engine/math/Math.h"
#include "engine/datatype/3D/Math3D.h"
#include "engine/exception/Exception.h"

typedef unsigned int uint;
typedef void (*function)();

// #EXTRA

#endif
