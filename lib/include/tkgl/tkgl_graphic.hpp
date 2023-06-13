#ifndef tkgl_graphic_hpp
#define tkgl_graphic_hpp

#include <tkgl/tkgl_base.hpp>
#include <tkgl/tkgl_shape.hpp>

namespace tkht {
namespace tkgl {
class Graphic {
public:
  char* path = nullptr;
  Color color;
  Color fillcolor;
  vector<shared_ptr<Shape>> shapes;

  ~Graphic();
  Graphic();
  
  void Write();
  void Read();
};
} // namespace tkgl
} // namespace tkht

#endif /* tkgl_graphic_hpp */
