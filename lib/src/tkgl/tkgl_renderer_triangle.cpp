#include <tkgl/tkgl_renderer_triangle.hpp>

namespace tkht {
namespace tkgl {
RendererTriangle::RendererTriangle(shared_ptr<Camera> camera, float depth)
    : Renderer(camera, depth, 3) {}

void RendererTriangle::GLFlush() {
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glDrawArrays(GL_TRIANGLES, 0, shader->count);
  glDisable(GL_BLEND);
}
} // namespace tkgl
} // namespace tkht
