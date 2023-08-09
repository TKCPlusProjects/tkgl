/// @file tkgl_shape_fan.hpp
#ifndef tkgl_shape_fan_hpp
#define tkgl_shape_fan_hpp

#include <tkgl/tkgl_shape.hpp>

namespace tkht
{
namespace tkgl
{
/// @brief 形状 扇形
class ShapeFan : public Shape {
public:
  /// @brief 填充
  bool is_solid = true;

  void refresh() override;
  void render() override;

  void write(std::shared_ptr<std::ofstream> ofs) override;
  void read(std::shared_ptr<std::ifstream> ifs) override;
};
}
}
#endif
