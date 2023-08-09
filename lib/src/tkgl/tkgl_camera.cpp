#include <tkgl/tkgl_camera.hpp>

namespace tkht
{
namespace tkgl
{
Camera::Viewport Camera::get_viewport(float window_width, float window_height) {
  if (window_width / window_height < aspect) {
    viewport.width  = window_width;
    viewport.height = window_width / aspect;
    viewport.x      = 0;
    viewport.y      = (window_height - viewport.height) / 2;
  } else {
    viewport.width  = window_height * aspect;
    viewport.height = window_height;
    viewport.x      = (window_width - viewport.width) / 2;
    viewport.y      = 0;
  }
  return viewport;
}

glm::mat4 Camera::get_projection_matrix() {
  return glm::perspective(glm::radians(fov), aspect, 0.1f, 100.0f);
}

glm::mat4 Camera::get_view_matrix() {
  return glm::lookAt(position, position + front, up);
}

void Camera::update() {
  float x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
  float y = sin(glm::radians(pitch));
  float z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
  front   = glm::normalize(glm::vec3(x, y, z));
  right   = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));
  up      = glm::normalize(glm::cross(right, front));
}

void Camera::process_movement(Movement direction, float delta_time) {
  float velocity = movement_speed * delta_time;
  if (direction == FORWARD) {
    position += front * velocity;
  }
  if (direction == BACKWARD) {
    position -= front * velocity;
  }
  if (direction == LEFT) {
    position -= right * velocity;
  }
  if (direction == RIGHT) {
    position += right * velocity;
  }
  if (direction == UP) {
    position += up * velocity;
  }
  if (direction == DOWN) {
    position -= up * velocity;
  }
}

void Camera::process_mouse_scroll(float offset_y) {
  fov -= (float)offset_y;
  if (fov < 1.0f) {
    fov = 1.0f;
  }
  if (fov > 90.0f) {
    fov = 90.0f;
  }
}

void Camera::process_mouse_focus(float x, float y, bool constrain_pitch) {
  if (focus_initialized) {
    process_mouse_movement(x - focus.x, focus.y - y, constrain_pitch);
  } else {
    focus_initialized = true;
  }
  focus = glm::vec2(x, y);
}

void Camera::process_mouse_movement(float offset_x, float offset_y, bool constrain_pitch) {
  yaw   += (offset_x * mouse_sensitivity);
  pitch += (offset_y * mouse_sensitivity);

  if (constrain_pitch) {
    if (pitch > 89.0f) {
      pitch = 89.0f;
    }
    if (pitch < -89.0f) {
      pitch = -89.0f;
    }
  }

  update();
}
}
}