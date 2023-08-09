#include <tkgl/tkgl_shape_circle.hpp>

namespace tkht
{
namespace tkgl
{
void ShapeCircle::set_radius(float radius) {
  this->radius = abs(radius);
  origin       = axis.position + radius * axis.x;
}

void ShapeCircle::set_origin(glm::vec3 origin) {
  this->origin = origin;
  axis.rotate(axis.x, origin - axis.position);
  radius = glm::distance(origin, axis.position);
}

void ShapeCircle::refresh() {
  clear();
  float radians_increment = glm::two_pi<float>() / segments;
  for (int i = 0; i < segments; ++i) {
    float     radians = radians_increment * i;
    float     scale_x = glm::cos(radians);
    float     scale_y = glm::sin(radians);
    glm::vec3 vertex  = axis.position + radius * (axis.x * scale_x + axis.y * scale_y);
    pos_list.push_back(vertex);
  }
}

void ShapeCircle::render() {
  if (is_solid) {
    glDrawArrays(GL_TRIANGLE_FAN, 0, pos_list.size());
  } else {
    glDrawArrays(GL_LINE_LOOP, 0, pos_list.size());
  }
}

void ShapeCircle::write(std::shared_ptr<std::ofstream> ofs) {
  ofs->write((char*)&axis, sizeof(Axis));
  ofs->write((char*)&radius, sizeof(float));
  ofs->write((char*)&origin, sizeof(glm::vec3));
  ofs->write((char*)&segments, sizeof(int));
  ofs->write((char*)&is_solid, sizeof(bool));
  ofs->write((char*)&color, sizeof(glm::vec4));
}

void ShapeCircle::read(std::shared_ptr<std::ifstream> ifs) {
  ifs->read((char*)&axis, sizeof(Axis));
  ifs->read((char*)&radius, sizeof(float));
  ifs->read((char*)&origin, sizeof(glm::vec3));
  ifs->read((char*)&segments, sizeof(int));
  ifs->read((char*)&is_solid, sizeof(bool));
  ifs->read((char*)&color, sizeof(glm::vec4));
}
}
}