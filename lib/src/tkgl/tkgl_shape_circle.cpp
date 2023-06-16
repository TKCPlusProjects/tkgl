#include <tkgl/tkgl_shape_circle.hpp>

namespace tkht {
namespace tkgl {
ShapeCircle::ShapeCircle() : Shape(TypeCircle) {}
ShapeCircle::ShapeCircle(float radius, Point center, bool is_solid) : Shape(TypeCircle), radius(radius), center(center), is_solid(is_solid) {
  CalPoint();
  CalVector();
}
ShapeCircle::ShapeCircle(Point center, Point point, bool is_solid) : Shape(TypeCircle), radius(Distance(point, center)), center(center), point(point), is_solid(is_solid) {
  CalRadius();
  CalVector();
}

void ShapeCircle::CalRadius() {
  radius = Distance(point, center);
}
void ShapeCircle::CalPoint() {
  point = center + radius * vector;
}
void ShapeCircle::CalVector() {
  vector = radius == 0 ? Point(1, 0) : 1/radius * (point - center);
}
void ShapeCircle::SetRadius(float radius) {
  this->radius = abs(radius);
  CalPoint();
}
void ShapeCircle::SetCenter(Point* center) {
  this->center = *center;
  CalRadius();
  CalVector();
}
void ShapeCircle::SetPoint(Point* point) {
  this->point = *point;
  CalRadius();
  CalVector();
}

void ShapeCircle::Write(ofstream* file) {
  file->write((char*)&radius, sizeof(float));
  file->write((char*)&center.x, sizeof(float));
  file->write((char*)&center.y, sizeof(float));
  file->write((char*)&is_solid, sizeof(bool));
}
void ShapeCircle::Read(ifstream* file) {
  file->read((char*)&radius, sizeof(float));
  file->read((char*)&center.x, sizeof(float));
  file->read((char*)&center.y, sizeof(float));
  file->read((char*)&is_solid, sizeof(bool));
  CalPoint();
  CalVector();
}
} // namespace tkgl
} // namespace tkht
