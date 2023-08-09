#include <tkgl/tkgl_shape_quad.hpp>

namespace tkht
{
namespace tkgl
{
void ShapeQuad::set_radius(float radius) {
  this->radius = glm::abs(radius);
}

void ShapeQuad::refresh() {
  clear();
  pos_list.push_back(axis.position - radius * axis.x + radius * axis.y);
  pos_list.push_back(axis.position + radius * axis.x + radius * axis.y);
  pos_list.push_back(axis.position + radius * axis.x - radius * axis.y);
  pos_list.push_back(axis.position - radius * axis.x - radius * axis.y);
}

void ShapeQuad::render() {
  glDrawArrays(GL_LINE_LOOP, 0, pos_list.size());
}

void ShapeQuad::write(std::shared_ptr<std::ofstream> ofs) {
  ofs->write((char*)&axis, sizeof(Axis));
  ofs->write((char*)&radius, sizeof(float));
  ofs->write((char*)&color, sizeof(glm::vec4));
}

void ShapeQuad::read(std::shared_ptr<std::ifstream> ifs) {
  ifs->read((char*)&axis, sizeof(Axis));
  ifs->read((char*)&radius, sizeof(float));
  ifs->read((char*)&color, sizeof(glm::vec4));
}
}
}