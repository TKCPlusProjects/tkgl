#include <tkgl/tkgl_renderer_point.hpp>

namespace tkht {
namespace tkgl {
RendererPoint::RendererPoint(shared_ptr<Camera> camera, float depth)
    : Renderer(camera, depth, 1) {}

void RendererPoint::GLFlush() {
  glEnable(GL_PROGRAM_POINT_SIZE);
  glDrawArrays(GL_POINTS, 0, shader->count);
  glDisable(GL_PROGRAM_POINT_SIZE);
}
} // namespace tkgl
} // namespace tkht
