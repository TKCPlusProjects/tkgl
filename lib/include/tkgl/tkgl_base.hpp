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

extern float kCircleSegments;
extern float kCircleIncrement;
extern float kSinInc;
extern float kCosInc;
void SetCircleSegments(float v);

struct Size {
  float w, h;
  Size() : w(0.0f), h(0.0f) {}
  Size(float w, float h) : w(w), h(h) {}
};
struct Point {
  float x, y;
  Point() : x(0.0f), y(0.0f) {}
  Point(float x, float y) : x(x), y(y) {}
};
struct Rotation {
  float s, c;
  Rotation() : s(sinf(0.0f)), c(cosf(0.0f)) {}
  Rotation(float angle) : s(sinf(angle)), c(cosf(angle)) {}
  void SetAngle(float angle) {
    s = sinf(angle);
    c = cosf(angle);
  }
};
struct Color {
  float r, g, b, a;
  Color() : r(0.0f), g(0.0f), b(0.0f), a(0.0f) {}
  Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}
};
struct Transform {
  Point p;
  Rotation q;
	Transform() {}
	Transform(Point p, Rotation q) : p(p), q(q) {}
};
inline Point operator + (const Point& a, const Point& b) { return Point(a.x + b.x, a.y + b.y); }
inline Point operator - (const Point& a, const Point& b) { return Point(a.x - b.x, a.y - b.y); }
inline Point operator * (float s, const Point& a) { return Point(s * a.x, s * a.y); }
inline Point Mul(const Transform& t, const Point& p) { return Point((t.q.c * p.x - t.q.s * p.y) + t.p.x, (t.q.s * p.x + t.q.c * p.y) + t.p.y); }
} // namespace tkgl
} // namespace tkht

#endif /* tkgl_base_hpp */
