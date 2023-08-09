/// @file tkgl_shader.hpp
#ifndef tkgl_shader_hpp
#define tkgl_shader_hpp

#include <tkgl/tkgl_base.hpp>

namespace tkht
{
namespace tkgl
{
/// @brief 着色器
class Shader {
public:
  /// @brief 分类名
  /// @param gl_shader_type OpenGL的着色器类型
  static const char* category_name(int gl_shader_type);
  /// @brief 加载着色器代码
  /// @param gl_shader_type OpenGL的着色器类型
  /// @param code OpenGL的着色器代码(GLSL)
  static GLuint      load_code(int gl_shader_type, const char* code);
  /// @brief 加载着色器代码文件
  /// @param gl_shader_type OpenGL的着色器类型
  /// @param path OpenGL的着色器代码(GLSL)文件路径
  static GLuint      load_file(int gl_shader_type, const char* path);

  GLuint             id     = 0;    ///< 着色器程序ID
  GLuint             vao    = 0;    ///< 顶点数组对象
  GLuint             vbo[2] = {0};  ///< 顶点缓冲对象数组
  std::vector<GLint> vap    = {};   ///< 顶点属性指针数组(顶点各组数据缓冲大小)

  ~Shader();
  /// @brief Shader
  /// @param vertex 顶点着色器
  /// @param fragment 片段着色器
  /// @param geometry 几何着色器
  /// @param tess_control 细分控制着色器
  /// @param tess_evaluation 细分评估着色器
  Shader(
    GLuint vertex,
    GLuint fragment,
    GLuint geometry        = 0,
    GLuint tess_control    = 0,
    GLuint tess_evaluation = 0
  );

  /// @brief 设置从顶点数组对象(vao)读取顶点数据的规则
  /// @param vap 顶点属性指针数组(顶点各组数据缓冲大小)
  void generate(std::vector<GLint> vap);
  /// @brief 启动着色器程序
  void use();

  /// @brief 设置bool类型uniform变量
  void set_bool(const std::string& name, bool value) const;
  /// @brief 设置int类型uniform变量
  void set_int(const std::string& name, int value) const;
  /// @brief 设置float类型uniform变量
  void set_float(const std::string& name, float value) const;
  /// @brief 设置vec2类型uniform变量
  void set_vec2(const std::string& name, const glm::vec2& value) const;
  /// @brief 设置vec3类型uniform变量
  void set_vec3(const std::string& name, const glm::vec3& value) const;
  /// @brief 设置vec4类型uniform变量
  void set_vec4(const std::string& name, const glm::vec4& value) const;
  /// @brief 设置mat2类型uniform变量
  void set_mat2(const std::string& name, const glm::mat2& mat) const;
  /// @brief 设置mat3类型uniform变量
  void set_mat3(const std::string& name, const glm::mat3& mat) const;
  /// @brief 设置mat4类型uniform变量
  void set_mat4(const std::string& name, const glm::mat4& mat) const;
};
}
}
#endif
