/// @file tkgl_window.hpp
#ifndef tkgl_window_hpp
#define tkgl_window_hpp

#include <tkgl/tkgl_base.hpp>

namespace tkht
{
namespace tkgl
{
class Window {
public:
  /// @brief 获取窗口
  static GLFWwindow *Root();

  /// @brief 初始化, 即将使用窗口时执行
  /// @param width 宽度
  /// @param height 高度
  /// @param title 标题
  /// @return int 成功:GL_TRUE, 失败:GL_FALSE
  static int Init(int width, int height, const char *title);

  /// @brief 设置帧缓冲区大小改变回调
  /// @param name 名称
  /// @param callback 回调
  static void
  SetSizeCallback(const char *name, std::function<void(int width, int height)> callback);
  /// @brief 移除帧缓冲区大小改变回调
  /// @param name 名称
  static void RemoveSizeCallback(const char *name);

  /// @brief 设置鼠标滚动回调
  /// @param name 名称
  /// @param callback 回调
  static void SetScrollCallback(
    const char *name, std::function<void(double offset_x, double offset_y)> callback
  );
  /// @brief 移除鼠标滚动回调
  /// @param name 名称
  static void RemoveScrollCallback(const char *name);

  /// @brief 设置鼠标位置回调
  /// @param name 名称
  /// @param callback 回调
  static void
  SetCursorCallback(const char *name, std::function<void(double x, double y)> callback);
  /// @brief 移除鼠标位置回调
  /// @param name 名称
  static void RemoveCursorCallback(const char *name);

  /// @brief 绘制窗口内容
  /// @param func 绘制函数
  static void Draw(std::function<void(float delta_time)> func);

  /// @brief 终止, 不再使用窗口时执行
  static void Terminate();
};
}
}
#endif
