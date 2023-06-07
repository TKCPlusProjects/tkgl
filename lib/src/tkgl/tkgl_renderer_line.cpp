#include <tkgl/tkgl_renderer_line.hpp>

namespace tkht {
namespace tkgl {
RendererLine::RendererLine(shared_ptr<Camera> camera, float depth)
    : Renderer(camera, depth, 2) {}

void RendererLine::GLFlush() { 
  glDrawArrays(GL_LINES, 0, shader->count);
}
} // namespace tkgl
} // namespace tkht
