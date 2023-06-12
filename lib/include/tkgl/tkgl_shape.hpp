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
class ShapePoint : public Shape {
public:
  float size;
  Point p;

  ShapePoint() : Shape(TypePoint) {}
  ShapePoint(float size, Point p) : Shape(TypePoint), size(size), p(p) {}

  void Write(ofstream* file) override;
  void Read(ifstream* file) override;
};
class ShapeSegment : public Shape {
public:
  vector<Point> vertexes;
  bool is_continue;

  ShapeSegment() : Shape(TypeSegment) {}
  ShapeSegment(vector<Point> vertexes, bool is_continue = false) : Shape(TypeSegment), vertexes(vertexes), is_continue(is_continue) {}

  void Write(ofstream* file) override;
  void Read(ifstream* file) override;
};
class ShapePolygon : public Shape {
public:
  vector<Point> vertexes;
  bool is_solid;

  ShapePolygon() : Shape(TypePolygon) {}
  ShapePolygon(vector<Point> vertexes, bool is_solid = false) : Shape(TypePolygon), vertexes(vertexes), is_solid(is_solid) {}

  void Write(ofstream* file) override;
  void Read(ifstream* file) override;
};
class ShapeCircle : public Shape {
public:
  Point center;
  float radius;
  bool is_solid;

  ShapeCircle() : Shape(TypeCircle) {}
  ShapeCircle(Point center, float radius, bool is_solid = false) : Shape(TypeCircle), center(center), radius(radius), is_solid(is_solid) {}

  void Write(ofstream* file) override;
  void Read(ifstream* file) override;
};
} // namespace tkgl
} // namespace tkht

#endif /* tkgl_shape_hpp */
