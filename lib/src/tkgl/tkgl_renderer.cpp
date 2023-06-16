#include <tkgl/tkgl_renderer.hpp>

namespace tkht {
namespace tkgl {
Renderer::Renderer(shared_ptr<Camera> camera, float depth, int dat_seg_len) : camera(camera), depth(depth), shader(make_shared<Shader>()) {
  shader->Generate(dat_seg_len);
  
  shader->Check();
  shader->Clean();
}

void Renderer::Push(float wide, float x, float y,
                    float r, float g, float b,
                    float a) {
  if (shader->IsFull()) Flush();
  shader->Push(wide, x, y, r, g, b, a);
}
void Renderer::Push(float wide, Point* point, Color* color) {
  if (shader->IsFull()) Flush();
  shader->Push(wide, point, color);
}
void Renderer::Push(Point* point, Color* color) {
  if (shader->IsFull()) Flush();
  shader->Push(1.0f, point, color);
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
