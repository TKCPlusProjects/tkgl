#ifndef tkgl_renderer_point_hpp
#define tkgl_renderer_point_hpp

#include <tkgl/tkgl_renderer.hpp>

namespace tkht {
namespace tkgl {
class RendererPoint : public Renderer {
public:
  RendererPoint(shared_ptr<Camera> camera, float depth);

  void GLFlush() override;
};
} // namespace tkgl
} // namespace tkht

#endif /* tkgl_renderer_point_hpp */
