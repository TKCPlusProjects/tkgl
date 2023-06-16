#include <tkgl/tkgl_shape_polygon.hpp>

namespace tkht {
namespace tkgl {
ShapePolygon::ShapePolygon() : Shape(TypePolygon) {}
ShapePolygon::ShapePolygon(vector<Point> vertexes, bool is_solid) : Shape(TypePolygon), vertexes(vertexes), is_solid(is_solid) {}

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
} // namespace tkgl
} // namespace tkht
