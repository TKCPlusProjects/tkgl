#include <tkgl/tkgl_shape_axis.hpp>

namespace tkht
{
namespace tkgl
{
void ShapeAxis::set_radius(float radius) {
  this->radius = glm::abs(radius);
}

void ShapeAxis::refresh() {
  clear();
  push(axis.position - radius * axis.x, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
  push(axis.position + radius * axis.x, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
  push(axis.position - radius * axis.y, glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
  push(axis.position + radius * axis.y, glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
  push(axis.position - radius * axis.z, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
  push(axis.position + radius * axis.z, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
}

void ShapeAxis::render() {
  glDrawArrays(GL_LINES, 0, pos_list.size());
}

void ShapeAxis::write(std::shared_ptr<std::ofstream> ofs) {
  ofs->write((char*)&axis, sizeof(Axis));
  ofs->write((char*)&radius, sizeof(float));
}

void ShapeAxis::read(std::shared_ptr<std::ifstream> ifs) {
  ifs->read((char*)&axis, sizeof(Axis));
  ifs->read((char*)&radius, sizeof(float));
}
}
}