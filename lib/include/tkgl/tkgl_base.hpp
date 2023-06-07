#ifndef tkgl_base_hpp
#define tkgl_base_hpp

#define GLFW_INCLUDE_NONE
#define GLEW_NO_GLU
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <tkcore/tkcore.hpp>

namespace tkht {
namespace tkgl {
struct Size {
  float w, h;
  Size(float w, float h) : w(w), h(h) {}
};
struct Point {
  float x, y;
  Point(float x, float y) : x(x), y(y) {}
};
struct Color {
  float r, g, b, a;
  Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}
};
} // namespace tkgl
} // namespace tkht

#endif /* tkgl_base_hpp */
