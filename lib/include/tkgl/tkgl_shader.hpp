#ifndef tkgl_shader_hpp
#define tkgl_shader_hpp

#include <tkgl/tkgl_base.hpp>

namespace tkht {
namespace tkgl {
class Shader {
public:
  const GLuint size_idx = 0;
  const GLuint vertex_idx = 1;
  const GLuint color_idx = 2;

  GLuint vs_id;
  GLuint fs_id;
  GLuint program_id;
  GLint proj_loc;

  GLuint vertex_arr;
  GLuint buffers[3];

  GLuint count;     // 当前缓存点个数
  GLuint count_max = 512; // 缓存点个数上限
  GLfloat *vertex_dat, *color_dat, *size_dat;

  ~Shader();
  Shader();

  void Check();
  void Clean();

  void Buffer(GLuint buffer, GLint index, GLint size, GLsizeiptr sizeiptr,
              const void *data);
  void Generate(GLint size);

  void Push(const GLfloat size, const GLfloat x, const GLfloat y,
            const GLfloat r, const GLfloat g, const GLfloat b, const GLfloat a);

  void BufferSub(GLuint buffer, GLint size, const void *data);
  void Flush(const GLfloat *matrix);

  bool IsFull();
  bool IsEmpty();
};
} // namespace tkgl
} // namespace tkht

#endif /* tkgl_shader_hpp */
