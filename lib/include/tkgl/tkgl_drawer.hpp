#ifndef tkgl_drawer_hpp
#define tkgl_drawer_hpp

#include <tkgl/tkgl_graphic.hpp>
#include <tkgl/tkgl_renderer.hpp>
#include <tkgl/tkgl_renderer_point.hpp>
#include <tkgl/tkgl_renderer_line.hpp>
#include <tkgl/tkgl_renderer_triangle.hpp>

namespace tkht {
namespace tkgl {
class Drawer {
public:
  shared_ptr<RendererPoint> point;
  shared_ptr<RendererLine> line;
  shared_ptr<RendererTriangle> triangle;

  Drawer(shared_ptr<Camera> camera, float depth);
  
  void DrawPoint(float wide, Point* vertex, int count, Color* color);
  void DrawSegment(Point* vertex, int count, Color* color);
  void DrawContinueSegment(Point* vertex, int count, Color* color);
  void DrawPolygon(Point* vertex, int count, Color* color);
  void DrawSolidPolygon(Point* vertex, int count, Color* color);
  void DrawCircle(Point* center, float r, Color* color);
  void DrawSolidCircle(Point* center, float r, Point* axis, Color* color);
  
  void DrawGraphic(Graphic* graphic, Transform* transform = nullptr);

  void Flush();
};
} // namespace tkgl
} // namespace tkht

#endif /* tkgl_drawer_hpp */
