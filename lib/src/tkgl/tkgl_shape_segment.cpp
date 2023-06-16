#include <tkgl/tkgl_shape_segment.hpp>

namespace tkht {
namespace tkgl {
ShapeSegment::ShapeSegment() : Shape(TypeSegment) {}
ShapeSegment::ShapeSegment(vector<Point> vertexes, bool is_continue) : Shape(TypeSegment), vertexes(vertexes), is_continue(is_continue) {}

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
} // namespace tkgl
} // namespace tkht
