#include <tkgl/tkgl_shape_point.hpp>

namespace tkht {
namespace tkgl {
ShapePoint::ShapePoint() : Shape(TypePoint) {}
ShapePoint::ShapePoint(float wide, vector<Point> vertexes) : Shape(TypePoint), wide(wide), vertexes(vertexes) {}

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
} // namespace tkgl
} // namespace tkht
