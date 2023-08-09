#include <tkgl/tkgl_axis.hpp>

namespace tkht
{
namespace tkgl
{
void Axis::set_position(glm::vec3 position) {
  this->position = position;
}

void Axis::set_rotation(glm::vec3 rotation) {
  this->rotation         = rotation;
  glm::mat4 rotation_mat = glm::mat4(1.0f);
  rotation_mat = glm::rotate(rotation_mat, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
  rotation_mat = glm::rotate(rotation_mat, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
  rotation_mat = glm::rotate(rotation_mat, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
  rotate(rotation_mat);
}

void Axis::rotate(glm::mat4 rotation_mat) {
  x = glm::vec3(rotation_mat * glm::vec4(x, 1.0f));
  y = glm::vec3(rotation_mat * glm::vec4(y, 1.0f));
  z = glm::vec3(rotation_mat * glm::vec4(z, 1.0f));
}

void Axis::rotate(glm::vec3 axis, float radians) {
  float angle  = glm::degrees(radians);
  rotation.x  += (1 * (axis.x > 0) - 1 * (axis.x < 0)) * angle;
  rotation.y  += (1 * (axis.y > 0) - 1 * (axis.y < 0)) * angle;
  rotation.z  += (1 * (axis.z > 0) - 1 * (axis.z < 0)) * angle;

  rotate(glm::rotate(glm::mat4(1.0f), radians, axis));
}

void Axis::rotate(glm::vec3 from, glm::vec3 to) {
  if (glm::length(from) * glm::length(to)) {
    from = glm::normalize(from);
    to   = glm::normalize(to);
    if (from == to) {
      return;
    }
    glm::vec3 axis;
    if (from == -1.0f * to) {
      if (from == x) {
        axis = z;
      } else {
        axis = x;
      }
    } else {
      axis = glm::cross(from, to);
    }
    float radians = glm::acos(glm::dot(from, to));
    rotate(axis, radians);
  }
}
}
}