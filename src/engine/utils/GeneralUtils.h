#ifndef __MT_GENERAL_UTILS_H__
#define __MT_GENERAL_UTILS_H__

namespace mt {
namespace engine {

class GeneralUtils {

public:

  // Swap value
  template <class T> static inline void swap(T &a, T &b)
  {
    T t = a;
    a = b;
    b = t;
  }

};

}}

#endif
