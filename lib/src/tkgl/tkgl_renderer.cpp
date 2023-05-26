#include <tkgl/tkgl_renderer.hpp>

namespace tkht {
namespace tkgl {
Renderer::Renderer(shared_ptr<Camera> camera, GLfloat depth, GLint dat_seg_len) : camera(camera), depth(depth), shader(make_shared<Shader>()) {
  shader->Generate(dat_seg_len);
  
  shader->Check();
  shader->Clean();
}

void Renderer::Push(const GLfloat size, const GLfloat x, const GLfloat y,
                    const GLfloat r, const GLfloat g, const GLfloat b,
                    const GLfloat a) {
  if (shader->IsFull()) {
    Flush();
  }

  shader->Push(size, x, y, r, g, b, a);
}

void Renderer::Flush() {
  if (shader->IsEmpty()) {
    return;
  }

  camera->BuildProjMatrix(depth);
  shader->Flush(camera->matrix);

  GLFlush();

  shader->Check();
  shader->Clean();
}
} // namespace tkgl
} // namespace tkht
