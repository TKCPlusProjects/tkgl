#include <tkgl/tkgl_shape_segment.hpp>

namespace tkht
{
namespace tkgl
{
void ShapeSegment::refresh() {
}

void ShapeSegment::render() {
  if (is_strip) {
    glDrawArrays(GL_LINE_STRIP, 0, pos_list.size());
  } else {
    glDrawArrays(GL_LINES, 0, pos_list.size());
  }
}

void ShapeSegment::write(std::shared_ptr<std::ofstream> ofs) {
  int count = (int)pos_list.size();
  ofs->write((char*)&count, sizeof(int));
  for (size_t i = 0; i < count; i++) {
    glm::vec3 vertex = pos_list.at(i);
    ofs->write((char*)&vertex, sizeof(glm::vec3));
  }
  ofs->write((char*)&color, sizeof(glm::vec4));
}

void ShapeSegment::read(std::shared_ptr<std::ifstream> ifs) {
  int count;
  ifs->read((char*)&count, sizeof(int));
  clear();
  for (size_t i = 0; i < count; i++) {
    glm::vec3 vertex;
    ifs->read((char*)&vertex, sizeof(glm::vec3));
    pos_list.push_back(vertex);
  }
  ifs->read((char*)&color, sizeof(glm::vec4));
}
}
}