/// @file tkgl_axis.hpp
#ifndef tkgl_axis_hpp
#define tkgl_axis_hpp

#include <tkgl/tkgl_base.hpp>

namespace tkht
{
namespace tkgl
{
/// @brief 坐标轴
class Axis {
public:
  glm::vec3 position = glm::vec3(0);           ///< 圆心
  glm::vec3 rotation = glm::vec3(0);           ///< 旋转
  glm::vec3 x        = glm::vec3(1.0f, 0, 0);  ///< 本地x轴单位向量
  glm::vec3 y        = glm::vec3(0, 1.0f, 0);  ///< 本地y轴单位向量
  glm::vec3 z        = glm::vec3(0, 0, 1.0f);  ///< 本地z轴单位向量

  /// @brief 设置位置
  /// @param position 三维位置坐标
  void set_position(glm::vec3 position);
  /// @brief 设置旋转角度
  /// @param rotation 三轴旋转角度
  void set_rotation(glm::vec3 rotation);

  /// @brief 旋转
  /// @param rotation_mat 旋转矩阵
  void rotate(glm::mat4 rotation_mat);
  /// @brief 旋转
  /// @param axis 旋转轴
  /// @param radians 旋转弧度
  void rotate(glm::vec3 axis, float radians);
  /// @brief 旋转
  /// @param from 起始向量
  /// @param to 结束向量
  void rotate(glm::vec3 from, glm::vec3 to);
};
}
}
#endif