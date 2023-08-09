/// @file tkgl_camera.hpp
#ifndef tkgl_camera_hpp
#define tkgl_camera_hpp

#include <tkgl/tkgl_base.hpp>

namespace tkht
{
namespace tkgl
{
/// @brief 相机
class Camera {
public:
  /// @brief 位移方式
  enum Movement {
    FORWARD,   ///< 向前
    BACKWARD,  ///< 向后
    LEFT,      ///< 向左
    RIGHT,     ///< 向右
    UP,        ///< 向上
    DOWN,      ///< 向下
  };

  /// @brief 视口：矩形
  struct Viewport {
    float x      = 0;
    float y      = 0;
    float width  = 0;
    float height = 0;
  };

  // cursor options
  glm::vec2        focus             = glm::vec2(0);  ///< 视线焦点
  bool             focus_initialized = false;         ///< 视线焦点初始化
  // camera options
  glm::vec3        position          = glm::vec3(0);  ///< 坐标
  float            movement_speed    = 2.5f;          ///< 速度
  float            mouse_sensitivity = 0.01f;         ///< 灵敏度
  float            fov               = 45.0f;         ///< 视野
  float            aspect            = 2.0f;          ///< 视野比例
  // euler Angles
  float            yaw               = -90.0f;  ///< 偏航角
  float            pitch             = 0.0f;    ///< 俯仰角
  // camera Attributes
  Camera::Viewport viewport;              ///< 视口
  glm::vec3        front = glm::vec3(0);  ///< 前方
  glm::vec3        right = glm::vec3(0);  ///< 右方
  glm::vec3        up    = glm::vec3(0);  ///< 上方

  /// @brief 获取视口
  /// @param window_width 窗口宽度
  /// @param window_height 窗口高度
  Camera::Viewport get_viewport(float window_width, float window_height);
  /// @brief 获取投射矩阵
  glm::mat4        get_projection_matrix();
  /// @brief 获取观察矩阵
  glm::mat4        get_view_matrix();

  /// @brief 更新相机状态
  void update();

  /// @brief 摄像头位移
  /// @param direction 方向
  /// @param delta_time 增量时间
  void process_movement(Movement direction, float delta_time);

  /// @brief 鼠标滚轮滑动
  /// @param offset_y y轴偏移量
  void process_mouse_scroll(float offset_y);
  /// @brief 鼠标视线焦点
  /// @param x x轴坐标
  /// @param y y轴坐标
  /// @param constrain_pitch 约束俯仰角
  void process_mouse_focus(float x, float y, bool constrain_pitch = true);
  /// @brief 鼠标视线焦点
  /// @param offset_x x轴坐标偏移量
  /// @param offset_y y轴坐标偏移量
  /// @param constrain_pitch 约束俯仰角
  void process_mouse_movement(float offset_x, float offset_y, bool constrain_pitch = true);
};
}
}
#endif
