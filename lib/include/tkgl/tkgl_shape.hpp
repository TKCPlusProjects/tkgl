/// @file tkgl_shape.hpp
#ifndef tkgl_shape_hpp
#define tkgl_shape_hpp

#include <tkgl/tkgl_base.hpp>
#include <tkgl/tkgl_camera.hpp>
#include <tkgl/tkgl_shader.hpp>

namespace tkht
{
namespace tkgl
{
/// @brief 形状
class Shape : public Shader {
private:
  bool               unicolor = true;
  static const char *vs_unicolor;
  static const char *vs_multicolor;
  static const char *fs_unicolor;
  static const char *fs_multicolor;
public:
  /// @brief Shape
  /// @param unicolor 是否为单色
  Shape(bool unicolor = true);

  /// @brief 通用颜色(单色模式下启用)
  glm::vec4 color = glm::vec4(1.0f);

  /// @brief 顶点坐标列表
  std::vector<glm::vec3> pos_list;
  /// @brief 顶点颜色列表
  std::vector<glm::vec4> col_list;

  /// @brief 添加顶点
  /// @param vertex 顶点坐标
  /// @param color 顶点颜色
  void push(glm::vec3 vertex, glm::vec4 color);
  /// @brief 插入顶点
  /// @param index 插入位置
  /// @param vertex 顶点坐标
  /// @param color 顶点颜色
  void insert(GLuint index, glm::vec3 vertex, glm::vec4 color);
  /// @brief 移除顶点
  /// @param index 移除位置
  void remove(GLuint index);
  /// @brief 清空顶点
  void clear();

  /// @brief 刷新顶点列表
  virtual void refresh() = 0;
  /// @brief 缓冲顶点列表
  void         buffer();

  /// @brief 渲染顶点列表
  virtual void render() = 0;
  /// @brief 在指定相机上完成渲染
  /// @param camera 指定相机
  void         flush(std::shared_ptr<Camera> camera);

  virtual void write(std::shared_ptr<std::ofstream> ofs) = 0;
  virtual void read(std::shared_ptr<std::ifstream> ifs)  = 0;
};
}
}
#endif
