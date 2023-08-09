#include <tkgl/tkgl_shape_fan.hpp>

namespace tkht
{
namespace tkgl
{
void ShapeFan::refresh() {
}

void ShapeFan::render() {
  if (is_solid) {
    glDrawArrays(GL_TRIANGLE_FAN, 0, pos_list.size());
  } else {
    glDrawArrays(GL_LINE_LOOP, 0, pos_list.size());
  }
}

void ShapeFan::write(std::shared_ptr<std::ofstream> ofs) {
  int count = (int)pos_list.size();
  ofs->write((char*)&count, sizeof(int));
  for (size_t i = 0; i < count; i++) {
    glm::vec3 vertex = pos_list.at(i);
    ofs->write((char*)&vertex, sizeof(glm::vec3));
  }
  ofs->write((char*)&is_solid, sizeof(bool));
  ofs->write((char*)&color, sizeof(glm::vec4));
}

void ShapeFan::read(std::shared_ptr<std::ifstream> ifs) {
  int count;
  ifs->read((char*)&count, sizeof(int));
  clear();
  for (size_t i = 0; i < count; i++) {
    glm::vec3 vertex;
    ifs->read((char*)&vertex, sizeof(glm::vec3));
    pos_list.push_back(vertex);
  }
  ifs->read((char*)&is_solid, sizeof(bool));
  ifs->read((char*)&color, sizeof(glm::vec4));
}
}
}