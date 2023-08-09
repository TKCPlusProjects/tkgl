/// @file tkgl_shape_axis.hpp
#ifndef tkgl_shape_axis_hpp
#define tkgl_shape_axis_hpp

#include <tkgl/tkgl_shape.hpp>
#include <tkgl/tkgl_axis.hpp>

namespace tkht
{
namespace tkgl
{
/// @brief 形状 坐标轴
class ShapeAxis : public Shape {
public:
  ShapeAxis() :
    Shape(false) {};

  /// @brief 坐标轴
  Axis  axis;
  /// @brief 半径
  float radius = 1.0f;
  
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