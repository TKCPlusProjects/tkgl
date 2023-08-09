/// @file tkgl_shape_segment.hpp
#ifndef tkgl_shape_segment_hpp
#define tkgl_shape_segment_hpp

#include <tkgl/tkgl_shape.hpp>

namespace tkht
{
namespace tkgl
{
/// @brief 形状 线段
class ShapeSegment : public Shape {
public:
  /// @brief 连续
  bool is_strip = true;

  void refresh() override;
  void render() override;

  void write(std::shared_ptr<std::ofstream> ofs) override;
  void read(std::shared_ptr<std::ifstream> ifs) override;
};
}
}
#endif
