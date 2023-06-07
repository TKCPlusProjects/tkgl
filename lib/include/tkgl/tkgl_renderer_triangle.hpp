#ifndef tkgl_renderer_triangle_hpp
#define tkgl_renderer_triangle_hpp

#include <tkgl/tkgl_renderer.hpp>

namespace tkht {
namespace tkgl {
class RendererTriangle : public Renderer {
public:
  RendererTriangle(shared_ptr<Camera> camera, float depth);

  void GLFlush() override;
};
} // namespace tkgl
} // namespace tkht

#endif /* tkgl_renderer_triangle_hpp */
