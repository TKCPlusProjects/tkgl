/// @file tkgl_shape_grid.hpp
#ifndef tkgl_shape_grid_hpp
#define tkgl_shape_grid_hpp

#include <tkgl/tkgl_shape.hpp>
#include <tkgl/tkgl_axis.hpp>

namespace tkht
{
namespace tkgl
{
/// @brief 形状 网格
class ShapeGrid : public Shape {
public:
  /// @brief 坐标轴
  Axis  axis;
  /// @brief 半径
  float radius  = 1.0f;
  /// @brief 密度：半径细分网格数量
  float density = 1.0f;

  /// @brief 设置半径
  void set_radius(float radius);
  /// @brief 设置密度：半径细分网格数量
  void set_density(float density);

  void refresh() override;
  void render() override;

  void write(std::shared_ptr<std::ofstream> ofs) override;
  void read(std::shared_ptr<std::ifstream> ifs) override;
};
}
}
#endif
