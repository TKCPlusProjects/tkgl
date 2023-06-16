#ifndef tkgl_shape_polygon_hpp
#define tkgl_shape_polygon_hpp

#include <tkgl/tkgl_shape.hpp>

namespace tkht {
namespace tkgl {
class ShapePolygon : public Shape {
public:
  vector<Point> vertexes;
  bool is_solid;

  ShapePolygon();
  ShapePolygon(vector<Point> vertexes, bool is_solid = false);

  void Write(ofstream* file) override;
  void Read(ifstream* file) override;
};
} // namespace tkgl
} // namespace tkht

#endif /* tkgl_shape_polygon_hpp */
