#ifndef tkgl_shader_hpp
#define tkgl_shader_hpp

#include <tkgl/tkgl_base.hpp>

namespace tkht {
namespace tkgl {
class Shader {
public:
  const int size_idx = 0;
  const int vertex_idx = 1;
  const int color_idx = 2;

  unsigned int vs_id;
  unsigned int fs_id;
  unsigned int program_id;
  int proj_loc;

  unsigned int vertex_arr;
  unsigned int buffers[3];

  int count;     // 当前缓存点个数
  int count_max = 384; // 缓存点个数上限
  float *vertex_dat, *color_dat, *size_dat;

  ~Shader();
  Shader();

  void Check();
  void Clean();

  void Buffer(unsigned int buffer, int index, int size, GLsizeiptr sizeiptr,
              const void *data);
  void Generate(int dat_seg_len);

  void Push(const float wide, const float x, const float y,
            const float r, const float g, const float b, const float a);
  void Push(const float wide, Point* point, Color* color);
  
  void BufferSub(unsigned int buffer, int size, const void *data);
  void Flush(const float *matrix);

  bool IsFull();
  bool IsEmpty();
};
} // namespace tkgl
} // namespace tkht

#endif /* tkgl_shader_hpp */
