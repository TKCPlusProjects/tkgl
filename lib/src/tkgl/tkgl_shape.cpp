#include <tkgl/tkgl_shape.hpp>

namespace tkht {
namespace tkgl {
void ShapePoint::Write(ofstream* file) {
  file->write((char*)&size, sizeof(float));
  file->write((char*)&p.x, sizeof(float));
  file->write((char*)&p.y, sizeof(float));
}
void ShapePoint::Read(ifstream* file) {
  file->read((char*)&size, sizeof(float));
  file->read((char*)&p.x, sizeof(float));
  file->read((char*)&p.y, sizeof(float));
}

void ShapeSegment::Write(ofstream* file) {
  file->write((char*)&o.x, sizeof(float));
  file->write((char*)&o.y, sizeof(float));
  file->write((char*)&t.x, sizeof(float));
  file->write((char*)&t.y, sizeof(float));
}
void ShapeSegment::Read(ifstream* file) {
  file->read((char*)&o.x, sizeof(float));
  file->read((char*)&o.y, sizeof(float));
  file->read((char*)&t.x, sizeof(float));
  file->read((char*)&t.y, sizeof(float));
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
  vertexes.clear();

  int count;
  file->read((char*)&count, sizeof(int));
  for (size_t i = 0; i < count; i++) {
      Point vertex;
      file->read((char*)&vertex.x, sizeof(float));
      file->read((char*)&vertex.y, sizeof(float));
      vertexes.push_back(vertex);
  }
  file->read((char*)&is_solid, sizeof(bool));
}

void ShapeCircle::Write(ofstream* file) {
  file->write((char*)&center.x, sizeof(float));
  file->write((char*)&center.y, sizeof(float));
  file->write((char*)&radius, sizeof(float));
  file->write((char*)&is_solid, sizeof(bool));
}
void ShapeCircle::Read(ifstream* file) {
  file->read((char*)&center.x, sizeof(float));
  file->read((char*)&center.y, sizeof(float));
  file->read((char*)&radius, sizeof(float));
  file->read((char*)&is_solid, sizeof(bool));
}
} // namespace tkgl
} // namespace tkht
