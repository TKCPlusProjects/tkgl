/// @file tkgl_shape_strip.hpp
#ifndef tkgl_shape_strip_hpp
#define tkgl_shape_strip_hpp

#include <tkgl/tkgl_shape.hpp>

namespace tkht
{
namespace tkgl
{
/// @brief 形状 条带
class ShapeStrip : public Shape {
public:
  void refresh() override;
  void render() override;

  void write(std::shared_ptr<std::ofstream> ofs) override;
  void read(std::shared_ptr<std::ifstream> ifs) override;
};
}
}
#endif
