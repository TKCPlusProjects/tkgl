#ifndef tkgl_base_hpp
#define tkgl_base_hpp

#define GLFW_INCLUDE_NONE
#define GLEW_NO_GLU
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <tkcore/tkcore.hpp>
#include <math.h>

namespace tkht {
namespace tkgl {
static const float kPI = 3.14159265359f;
static const float kCircleSegments = 16.0f;
static const float kCircleIncrement = 2.0f * kPI / kCircleSegments;
static const float kSinInc = sinf(kCircleIncrement);
static const float kCosInc = cosf(kCircleIncrement);

struct Size {
  float w, h;
  Size(float w, float h) : w(w), h(h) {}
};
struct Point {
  float x, y;
  Point(float x, float y) : x(x), y(y) {}
};
inline Point operator + (const Point& a, const Point& b) { return Point(a.x + b.x, a.y + b.y); }
inline Point operator - (const Point& a, const Point& b) { return Point(a.x - b.x, a.y - b.y); }
inline Point operator * (float s, const Point& a) { return Point(s * a.x, s * a.y); }
struct Color {
  float r, g, b, a;
  Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}
};
} // namespace tkgl
} // namespace tkht

#endif /* tkgl_base_hpp */
