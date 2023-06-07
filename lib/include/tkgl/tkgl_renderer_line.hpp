#ifndef tkgl_renderer_line_hpp
#define tkgl_renderer_line_hpp

#include <tkgl/tkgl_renderer.hpp>

namespace tkht {
namespace tkgl {
class RendererLine : public Renderer {
public:
  RendererLine(shared_ptr<Camera> camera, float depth);

  void GLFlush() override;
};
} // namespace tkgl
} // namespace tkht

#endif /* tkgl_renderer_line_hpp */
