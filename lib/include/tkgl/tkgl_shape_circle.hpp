#ifndef tkgl_shape_circle_hpp
#define tkgl_shape_circle_hpp

#include <tkgl/tkgl_shape.hpp>

namespace tkht {
namespace tkgl {
class ShapeCircle : public Shape {
protected:
  Point vector;
public:
  float radius;
  Point center;
  Point point;
  bool is_solid;

  ShapeCircle();
  ShapeCircle(float radius, Point center, bool is_solid = false);
  ShapeCircle(Point center, Point point, bool is_solid = false);

  void CalVector();
  void CalRadius();
  void CalPoint();
  void SetRadius(float radius);
  void SetCenter(Point* center);
  void SetPoint(Point* point);

  void Write(ofstream* file) override;
  void Read(ifstream* file) override;
};
} // namespace tkgl
} // namespace tkht

#endif /* tkgl_shape_circle_hpp */
