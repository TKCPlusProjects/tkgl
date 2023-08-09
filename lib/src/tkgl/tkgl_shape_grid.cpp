#include <tkgl/tkgl_shape_grid.hpp>

namespace tkht
{
namespace tkgl
{
void ShapeGrid::set_radius(float radius) {
  this->radius = glm::abs(radius);
}

void ShapeGrid::set_density(float density) {
  this->density = glm::abs(density);
}

void ShapeGrid::refresh() {
  clear();
  for (int i = -1 * density; i <= +1 * density; i++) {
    float inc = radius / density * i;
    pos_list.push_back(axis.position - radius * axis.x + inc * axis.y);
    pos_list.push_back(axis.position + radius * axis.x + inc * axis.y);
    pos_list.push_back(axis.position - radius * axis.y + inc * axis.x);
    pos_list.push_back(axis.position + radius * axis.y + inc * axis.x);
  }
}

void ShapeGrid::render() {
  glDrawArrays(GL_LINES, 0, pos_list.size());
}

void ShapeGrid::write(std::shared_ptr<std::ofstream> ofs) {
  ofs->write((char*)&axis, sizeof(Axis));
  ofs->write((char*)&radius, sizeof(float));
  ofs->write((char*)&density, sizeof(float));
  ofs->write((char*)&color, sizeof(glm::vec4));
}

void ShapeGrid::read(std::shared_ptr<std::ifstream> ifs) {
  ifs->read((char*)&axis, sizeof(Axis));
  ifs->read((char*)&radius, sizeof(float));
  ifs->read((char*)&density, sizeof(float));
  ifs->read((char*)&color, sizeof(glm::vec4));
}
}
}