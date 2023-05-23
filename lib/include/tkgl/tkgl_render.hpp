#ifndef tkgl_render_hpp
#define tkgl_render_hpp

#include <tkgl/tkgl_camera.hpp>
#include <tkgl/tkgl_base.hpp>
#include <tkgl/tkgl_shader.hpp>

namespace tkht {
namespace tkgl {
struct Renderer {
  Camera *camera; // 视野相机
  GLfloat depth;  // 渲染深度

  Shader *shader; // 着色器

  const int dat_seg_count = 512; // 总图形的数量

  /// @brief 初始化
  /// @param _camera 视野相机
  /// @param _depth 渲染深度
  /// @param _dat_seg_len 每一个图形的点的个数
  Renderer(Camera *_camera, GLfloat _depth, GLint _dat_seg_len);

  void Push(const GLfloat size, const GLfloat x, const GLfloat y,
            const GLfloat r, const GLfloat g, const GLfloat b, const GLfloat a);
  void Flush();

  virtual void GLFlush() = 0;
};
} // namespace tkgl
} // namespace tkht

#endif /* tkgl_render_hpp */
