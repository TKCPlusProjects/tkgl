#ifndef tkgl_renderer_hpp
#define tkgl_renderer_hpp

#include <tkgl/tkgl_camera.hpp>
#include <tkgl/tkgl_base.hpp>
#include <tkgl/tkgl_shader.hpp>

namespace tkht {
namespace tkgl {
class Renderer {
public:
  shared_ptr<Camera> camera; // 视野相机
  float depth;  // 渲染深度

  shared_ptr<Shader> shader; // 着色器

  /// @brief 初始化
  /// @param camera 视野相机
  /// @param depth 渲染深度
  /// @param dat_seg_len 每一个图形的点的个数
  Renderer(shared_ptr<Camera> camera, float depth, int dat_seg_len);

  void Push(float wide, float x, float y,
            float r, float g, float b, float a);
  void Push(float wide, Point* point, Color* color);
  void Push(Point* point, Color* color);
  void Flush();

  virtual void GLFlush() = 0;
};
} // namespace tkgl
} // namespace tkht

#endif /* tkgl_renderer_hpp */
