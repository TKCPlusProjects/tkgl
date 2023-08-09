/// @file tkgl_shape_quad.hpp
#ifndef tkgl_shape_quad_hpp
#define tkgl_shape_quad_hpp

#include <tkgl/tkgl_shape.hpp>
#include <tkgl/tkgl_axis.hpp>

namespace tkht
{
namespace tkgl
{
/// @brief 形状 网格
class ShapeQuad : public Shape {
public:
  /// @brief 坐标轴
  Axis  axis;
  /// @brief 半径
  float radius   = 1.0f;
  /// @brief 填充
  bool  is_solid = true;

  /// @brief 设置半径
  void set_radius(float radius);

  void refresh() override;
  void render() override;

  void write(std::shared_ptr<std::ofstream> ofs) override;
  void read(std::shared_ptr<std::ifstream> ifs) override;
};
}
}
#endif
