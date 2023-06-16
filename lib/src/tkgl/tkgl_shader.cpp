#include <tkgl/tkgl_shader.hpp>

namespace tkht {
namespace tkgl {
const char *vs = "#version 330\n"
                 "layout(location = 0) in float v_size;\n"
                 "layout(location = 1) in vec2 v_position;\n"
                 "layout(location = 2) in vec4 v_color;\n"
                 "out vec4 f_color;\n"
                 "uniform mat4 proj_matrix;\n"
                 "void main(void)\n"
                 "{\n"
                 "  f_color = v_color;\n"
                 "  gl_Position = proj_matrix * vec4(v_position, 0.0f, 1.0f);\n"
                 "  gl_PointSize = v_size;\n"
                 "}\n";

const char *fs = "#version 330\n"
                 "in vec4 f_color;\n"
                 "out vec4 color;\n"
                 "void main(void)\n"
                 "{\n"
                 "  color = f_color;\n"
                 "}\n";

const char *matrix_name = "proj_matrix";

unsigned int ShaderFromString(const char *source, GLenum type) {
  const char *sources[] = {source};

  unsigned int res = glCreateShader(type);
  glShaderSource(res, 1, sources, NULL);
  glCompileShader(res);

  int compile_ok = GL_FALSE;
  glGetShaderiv(res, GL_COMPILE_STATUS, &compile_ok);
  if (compile_ok == GL_FALSE) {
    glDeleteShader(res);
    return 0;
  }

  return res;
}

unsigned int ShaderProgram(const char *vs, const char *fs) {
  unsigned int vs_id = ShaderFromString(vs, GL_VERTEX_SHADER);
  Assert(vs_id != 0, "GL_VERTEX_SHADER 着色器编译失败");
  unsigned int fs_id = ShaderFromString(fs, GL_FRAGMENT_SHADER);
  Assert(fs_id != 0, "GL_FRAGMENT_SHADER 着色器编译失败");

  unsigned int program_id = glCreateProgram();
  glAttachShader(program_id, vs_id);
  glAttachShader(program_id, fs_id);
  glBindFragDataLocation(program_id, 0, "color");
  glLinkProgram(program_id);

  glDeleteShader(vs_id);
  glDeleteShader(fs_id);

  int status = GL_FALSE;
  glGetProgramiv(program_id, GL_LINK_STATUS, &status);
  Assert(status != GL_FALSE, "着色器程序连接失败");

  return program_id;
}

Shader::~Shader() {
  delete size_dat;
  delete vertex_dat;
  delete color_dat;
  glDeleteBuffers(3, buffers);
  glDeleteVertexArrays(1, &vertex_arr);
  vertex_arr = 0;
  glDeleteProgram(program_id);
  program_id = 0;
}

Shader::Shader() {
  program_id = ShaderProgram(vs, fs); // 创建着色器程序
  proj_loc = glGetUniformLocation(
      program_id, matrix_name); // 获取投影矩阵 proj_matrix 的位置
}

void Shader::Check() {
  GLenum err = glGetError();
  Assert(err == GL_NO_ERROR, "OpenGL 错误码 %d", err);
}

void Shader::Clean() {
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
  glUseProgram(0);
  count = 0;
}

void Shader::Buffer(unsigned int buffer, int index, int size, GLsizeiptr sizeiptr,
                    const void *data) {
  glBindBuffer(GL_ARRAY_BUFFER, buffer);
  glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, 0, ((const void *)(0)));
  glBufferData(GL_ARRAY_BUFFER, sizeiptr, data, GL_DYNAMIC_DRAW);
}

void Shader::Generate(int dat_seg_len) {
  int size = count_max * dat_seg_len;
  size_dat = new float[1 * size];
  vertex_dat = new float[2 * size];
  color_dat = new float[4 * size];
  
  glGenVertexArrays(1, &vertex_arr); // 生成一个顶点数组
  glGenBuffers(3, buffers);          // 生成三个缓冲区

  glBindVertexArray(vertex_arr);
  glEnableVertexAttribArray(size_idx);
  glEnableVertexAttribArray(vertex_idx);
  glEnableVertexAttribArray(color_idx);

  Buffer(buffers[size_idx], size_idx, 1, 1 * size * sizeof(float), size_dat);
  Buffer(buffers[vertex_idx], vertex_idx, 2, 2 * size * sizeof(float), vertex_dat);
  Buffer(buffers[color_idx], color_idx, 4, 4 * size * sizeof(float), color_dat);
}

void Shader::Push(const float wide, const float x, const float y,
                  const float r, const float g, const float b,
                  const float a) {
  size_dat[1 * count + 0] = wide;

  vertex_dat[2 * count + 0] = x;
  vertex_dat[2 * count + 1] = y;

  color_dat[4 * count + 0] = r;
  color_dat[4 * count + 1] = g;
  color_dat[4 * count + 2] = b;
  color_dat[4 * count + 3] = a;

  ++count;
}
void Shader::Push(const float wide, Point* point, Color* color) {
  Push(wide, point->x, point->y, color->r, color->g, color->b, color->a);
}

void Shader::BufferSub(unsigned int buffer, int size, const void *data) {
  glBindBuffer(GL_ARRAY_BUFFER, buffer);
  glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}

void Shader::Flush(const float *matrix) {
  glUseProgram(program_id);
  glUniformMatrix4fv(proj_loc, 1, GL_FALSE, matrix);

  glBindVertexArray(vertex_arr);
  BufferSub(buffers[size_idx], 1 * count * sizeof(float), size_dat);
  BufferSub(buffers[vertex_idx], 2 * count * sizeof(float), vertex_dat);
  BufferSub(buffers[color_idx], 4 * count * sizeof(float), color_dat);
}

bool Shader::IsFull() { return count == count_max; }
bool Shader::IsEmpty() { return count == 0; }
} // namespace tkgl
} // namespace tkht
