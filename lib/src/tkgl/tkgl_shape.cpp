#include <tkgl/tkgl_shape.hpp>

namespace tkht {
namespace tkgl {
void ShapePoint::Write(ofstream* file) {
  file->write((char*)&wide, sizeof(float));
  int count = (int)vertexes.size();
  file->write((char*)&count, sizeof(int));
  for (size_t i = 0; i < count; i++) {
    Point vertex = vertexes[i];
    file->write((char*)&vertex.x, sizeof(float));
    file->write((char*)&vertex.y, sizeof(float));
  }
}
void ShapePoint::Read(ifstream* file) {
  file->read((char*)&wide, sizeof(float));
  int count;
  file->read((char*)&count, sizeof(int));
  vertexes.clear();
  for (size_t i = 0; i < count; i++) {
      Point vertex;
      file->read((char*)&vertex.x, sizeof(float));
      file->read((char*)&vertex.y, sizeof(float));
      vertexes.push_back(vertex);
  }
}

void ShapeSegment::Write(ofstream* file) {
  int count = (int)vertexes.size();
  file->write((char*)&count, sizeof(int));
  for (size_t i = 0; i < count; i++) {
    Point vertex = vertexes[i];
    file->write((char*)&vertex.x, sizeof(float));
    file->write((char*)&vertex.y, sizeof(float));
  }
  file->write((char*)&is_continue, sizeof(bool));
}
void ShapeSegment::Read(ifstream* file) {
  int count;
  file->read((char*)&count, sizeof(int));
  vertexes.clear();
  for (size_t i = 0; i < count; i++) {
      Point vertex;
      file->read((char*)&vertex.x, sizeof(float));
      file->read((char*)&vertex.y, sizeof(float));
      vertexes.push_back(vertex);
  }
  file->read((char*)&is_continue, sizeof(bool));
}

void ShapePolygon::Write(ofstream* file) {
  int count = (int)vertexes.size();
  file->write((char*)&count, sizeof(int));
  for (size_t i = 0; i < count; i++) {
    Point vertex = vertexes[i];
    file->write((char*)&vertex.x, sizeof(float));
    file->write((char*)&vertex.y, sizeof(float));
  }
  file->write((char*)&is_solid, sizeof(bool));
}
void ShapePolygon::Read(ifstream* file) {
  int count;
  file->read((char*)&count, sizeof(int));
  vertexes.clear();
  for (size_t i = 0; i < count; i++) {
      Point vertex;
      file->read((char*)&vertex.x, sizeof(float));
      file->read((char*)&vertex.y, sizeof(float));
      vertexes.push_back(vertex);
  }
  file->read((char*)&is_solid, sizeof(bool));
}

void ShapeCircle::SetRadius(float radius) {
  this->radius = radius;
  point *= (radius / point.Length());
}
void ShapeCircle::SetCenter(Point* center) {
  this->center = *center;
  radius = Distance(*center, point);
}
void ShapeCircle::SetPoint(Point* point) {
  this->point = *point;
  radius = Distance(center, *point);
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
}
} // namespace tkgl
} // namespace tkht
