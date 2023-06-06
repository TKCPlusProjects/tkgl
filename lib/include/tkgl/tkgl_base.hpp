#ifndef tkgl_base_hpp
#define tkgl_base_hpp

#define GLFW_INCLUDE_NONE
#define GLEW_NO_GLU
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <tkcore/tkcore.hpp>

namespace tkht {
namespace tkgl {
struct Point {
  float x, y;
  Point(float x, float y) : x(x), y(y) {}
};
} // namespace tkgl
} // namespace tkht

#endif /* tkgl_base_hpp */
