#include <tkgl/tkgl_shader.hpp>

namespace tkht
{
namespace tkgl
{
const char* Shader::category_name(int gl_shader_type) {
  const char* name = "";
  switch (gl_shader_type) {
  case GL_VERTEX_SHADER: {
    name = "vertex";
  } break;
  case GL_FRAGMENT_SHADER: {
    name = "fragment";
  } break;
  case GL_GEOMETRY_SHADER: {
    name = "geometry";
  } break;
  case GL_TESS_CONTROL_SHADER: {
    name = "tess_control";
  } break;
  case GL_TESS_EVALUATION_SHADER: {
    name = "tess_evaluationuation";
  } break;
  default: {
    tkht::Err("着色器类型错误");
    return GL_FALSE;
  } break;
  }
  return name;
}

GLuint Shader::load_code(int gl_shader_type, const char* code) {
  const char* category = category_name(gl_shader_type);

  GLuint shader = glCreateShader(gl_shader_type);
  glShaderSource(shader, 1, &code, NULL);
  glCompileShader(shader);

  int status = GL_FALSE;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
  if (status == GL_FALSE) {
    char infoLog[1024];
    glGetShaderInfoLog(shader, 1024, NULL, infoLog);
    tkht::Err("%s 着色器编译失败: %s", category, infoLog);
    glDeleteShader(shader);
    return GL_FALSE;
  }

  return shader;
}

GLuint Shader::load_file(int gl_shader_type, const char* path) {
  const char* category = category_name(gl_shader_type);

  if (path == nullptr) {
    tkht::Err("%s 着色器文件路径为空", category);
    return GL_FALSE;
  }

  std::stringstream ss;
  try {
    std::ifstream fs;
    fs.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fs.open(path);
    ss << fs.rdbuf();
    fs.close();
  } catch (std::ifstream::failure& e) {
    tkht::Err("%s 着色器文件读取失败: %s", e.what());
    return GL_FALSE;
  }

  std::string s      = ss.str();
  const char* code   = s.c_str();
  GLuint      shader = load_code(gl_shader_type, code);

  return shader;
}

Shader::~Shader() {
  glDeleteVertexArrays(1, &vao);
  glDeleteBuffers(vap.size(), vbo);
}

Shader::Shader(
  GLuint vertex, GLuint fragment, GLuint geometry, GLuint tess_control, GLuint tess_evaluation
) {
  id = glCreateProgram();

  if (id == 0) {
    tkht::Err("着色器程序初始化失败");
  }

  if (vertex) {
    glAttachShader(id, vertex);
  }
  if (fragment) {
    glAttachShader(id, fragment);
  }
  if (geometry) {
    glAttachShader(id, geometry);
  }
  if (tess_control) {
    glAttachShader(id, tess_control);
  }
  if (tess_evaluation) {
    glAttachShader(id, tess_evaluation);
  }

  glLinkProgram(id);

  int status = GL_FALSE;
  glGetProgramiv(id, GL_LINK_STATUS, &status);
  if (status == GL_FALSE) {
    char infoLog[1024];
    glGetProgramInfoLog(id, 1024, NULL, infoLog);
    tkht::Err("着色器程序连接失败: %s", infoLog);
    glDeleteProgram(id);
  }
}

void Shader::generate(std::vector<GLint> vap) {
  this->vap = vap;

  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  glGenBuffers(vap.size(), vbo);
  for (GLuint i = 0, offset = 0; i < vap.size(); i++) {
    GLuint size = vap[i];
    glBindBuffer(GL_ARRAY_BUFFER, vbo[i]);
    glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_STATIC_DRAW);
    glVertexAttribPointer(
      i, size, GL_FLOAT, GL_FALSE, sizeof(float) * size, (void*)(sizeof(float) * 0)
    );
    glEnableVertexAttribArray(i);
    glEnableVertexAttribArray(i);
    offset += size;
  }
}

void Shader::use() {
  glUseProgram(id);
  glBindVertexArray(vao);
}

void Shader::set_bool(const std::string& name, bool value) const {
  glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
}

void Shader::set_int(const std::string& name, int value) const {
  glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::set_float(const std::string& name, float value) const {
  glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::set_vec2(const std::string& name, const glm::vec2& value) const {
  glUniform2fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]);
}

void Shader::set_vec3(const std::string& name, const glm::vec3& value) const {
  glUniform3fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]);
}

void Shader::set_vec4(const std::string& name, const glm::vec4& value) const {
  glUniform4fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]);
}

void Shader::set_mat2(const std::string& name, const glm::mat2& mat) const {
  glUniformMatrix2fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::set_mat3(const std::string& name, const glm::mat3& mat) const {
  glUniformMatrix3fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::set_mat4(const std::string& name, const glm::mat4& mat) const {
  glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
}
}