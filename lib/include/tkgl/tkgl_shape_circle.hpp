/// @file tkgl_shape_circle.hpp
#ifndef tkgl_shape_circle_hpp
#define tkgl_shape_circle_hpp

#include <tkgl/tkgl_shape.hpp>
#include <tkgl/tkgl_axis.hpp>

namespace tkht
{
namespace tkgl
{
/// @brief 形状 圆形
class ShapeCircle : public Shape {
public:
  /// @brief 坐标轴
  Axis      axis;
  /// @brief 半径
  float     radius   = 1.0f;
  /// @brief 圆上首位顶点
  glm::vec3 origin   = glm::vec3(1.0f, 0, 0);
  /// @brief 圆拆分线段数
  int       segments = 16;
  /// @brief 填充
  bool      is_solid = true;

  /// @brief 设置半径
  void set_radius(float radius);
  /// @brief 设置圆上首位顶点
  void set_origin(glm::vec3 origin);

  void refresh() override;
  void render() override;

  void write(std::shared_ptr<std::ofstream> ofs) override;
  void read(std::shared_ptr<std::ifstream> ifs) override;
};
}
}
#endif