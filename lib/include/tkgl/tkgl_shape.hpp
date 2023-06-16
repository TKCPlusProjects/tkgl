#ifndef tkgl_shape_hpp
#define tkgl_shape_hpp

#include <tkgl/tkgl_base.hpp>

namespace tkht {
namespace tkgl {
class Shape {
public:
  enum Type : int {
		TypePoint = 0,
    TypeSegment = 1,
		TypePolygon = 2,
    TypeCircle = 3,
	};

  Type type;
  Shape(Type type) : type(type) {};

  virtual void Write(ofstream* file) = 0;
  virtual void Read(ifstream* file) = 0;
};
} // namespace tkgl
} // namespace tkht

#endif /* tkgl_shape_hpp */
