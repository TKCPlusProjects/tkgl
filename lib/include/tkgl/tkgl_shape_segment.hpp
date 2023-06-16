#ifndef tkgl_shape_segment_hpp
#define tkgl_shape_segment_hpp

#include <tkgl/tkgl_shape.hpp>

namespace tkht {
namespace tkgl {
class ShapeSegment : public Shape {
public:
  vector<Point> vertexes;
  bool is_continue;

  ShapeSegment();
  ShapeSegment(vector<Point> vertexes, bool is_continue = false);

  void Write(ofstream* file) override;
  void Read(ifstream* file) override;
};
} // namespace tkgl
} // namespace tkht

#endif /* tkgl_shape_segment_hpp */
