#include <tkgl/tkgl_shape_strip.hpp>

namespace tkht
{
namespace tkgl
{
void ShapeStrip::refresh() {
}

void ShapeStrip::render() {
  glDrawArrays(GL_TRIANGLE_STRIP, 0, pos_list.size());
}

void ShapeStrip::write(std::shared_ptr<std::ofstream> ofs) {
  int count = (int)pos_list.size();
  ofs->write((char*)&count, sizeof(int));
  for (size_t i = 0; i < count; i++) {
    glm::vec3 vertex = pos_list.at(i);
    ofs->write((char*)&vertex, sizeof(glm::vec3));
  }
  ofs->write((char*)&color, sizeof(glm::vec4));
}

void ShapeStrip::read(std::shared_ptr<std::ifstream> ifs) {
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