#ifndef tkgl_graphic_hpp
#define tkgl_graphic_hpp

#include <tkgl/tkgl_base.hpp>
#include <tkgl/tkgl_shape.hpp>

namespace tkht {
namespace tkgl {
class Graphic {
public:
  const char* path;
  Color color;
  Color fillcolor;
  vector<shared_ptr<Shape>> shapes;
  
  void Write();
  void Read();
};
} // namespace tkgl
} // namespace tkht

#endif /* tkgl_graphic_hpp */
