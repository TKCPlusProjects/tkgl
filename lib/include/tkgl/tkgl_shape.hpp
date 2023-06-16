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
  float wide;
  vector<Point> vertexes;

  ShapePoint() : Shape(TypePoint) {}
  ShapePoint(float wide, vector<Point> vertexes) : Shape(TypePoint), wide(wide), vertexes(vertexes) {}

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
protected:
  Point vector;
public:
  float radius;
  Point center;
  Point point;
  bool is_solid;

  ShapeCircle() : Shape(TypeCircle) {}
  ShapeCircle(float radius, Point center, Point point, bool is_solid = false) : Shape(TypeCircle), radius(radius), center(center), point(point), is_solid(is_solid), vector(Distance(center, point) == 0 ? Point(1, 0) : (point - center)) {}
  ShapeCircle(float radius, Point center, bool is_solid = false) : ShapeCircle(radius, center, Point(center.x + radius, center.y), is_solid) {}
  ShapeCircle(Point center, Point point, bool is_solid = false) : ShapeCircle(Distance(center, point), center, point, is_solid) {}

  void SetRadius(float radius);
  void SetCenter(Point* center);
  void SetPoint(Point* point);

  void Write(ofstream* file) override;
  void Read(ifstream* file) override;
};
} // namespace tkgl
} // namespace tkht

#endif /* tkgl_shape_hpp */
