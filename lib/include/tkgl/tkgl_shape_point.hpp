#ifndef tkgl_shape_point_hpp
#define tkgl_shape_point_hpp

#include <tkgl/tkgl_shape.hpp>

namespace tkht {
namespace tkgl {
class ShapePoint : public Shape {
public:
  float wide;
  vector<Point> vertexes;

  ShapePoint();
  ShapePoint(float wide, vector<Point> vertexes);

  void Write(ofstream* file) override;
  void Read(ifstream* file) override;
};
} // namespace tkgl
} // namespace tkht

#endif /* tkgl_shape_point_hpp */
