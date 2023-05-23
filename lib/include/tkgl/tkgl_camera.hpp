#ifndef tkgl_camera_hpp
#define tkgl_camera_hpp

#include <tkgl/tkgl_base.hpp>

namespace tkht {
namespace tkgl {
struct Camera {
  /// @brief 单位长度
  float unit;
  /// @brief 相机尺寸
  int width, height = 0;
  /// @brief 缩放比例
  float zoom = 1.0f;
  /// @brief 中心点
  float center_x, center_y;
  /// @brief 左下角坐标
  float lower_x, lower_y;
  /// @brief 右上角坐标
  float upper_x, upper_y;
  /// @brief 坐标映射矩阵
  float matrix[16] = {0.0f};

  Camera(float _unit);

  /// @brief 重置视图，中心点和缩放比例
  void ResetView();

  /// @brief 设置宽高，并计算视图左下点和右上点的坐标
  void SetSize(int _width, int _height);
  /// @brief 设置缩放，并计算视图左下点和右上点的坐标
  void SetZoom(float _zoom);
  /// @brief 计算视图左下点和右上点的坐标
  void Calculate();

  /// @brief 构建投影矩阵
  /// @param depth 深度偏移量
  void BuildProjMatrix(float depth);

  /// @brief 转换屏幕坐标到世界坐标
  /// @param x,y 世界坐标
  /// @param screen_x,screen_y 屏幕坐标
  void ConvertScreenToWorld(float *x, float *y, const float screen_x,
                            const float screen_y);
  /// @brief 转换屏幕坐标到世界坐标
  /// @param x,y 屏幕坐标
  /// @param world_x,world_y 世界坐标
  void ConvertWorldToScreen(float *x, float *y, const float world_x,
                            const float world_y);
};
} // namespace tkgl
} // namespace tkht

#endif /* tkgl_camera_hpp */
