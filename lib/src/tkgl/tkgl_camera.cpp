#include <tkgl/tkgl_camera.hpp>

namespace tkht {
namespace tkgl {
Camera::Camera(float unit) : unit(unit) {
  ResetView();
}

void Camera::ResetView() {
  SetZoom(1.0f);
  SetCenter(0.0f, 0.0f);
}

void Camera::SetSize(int width, int height) {
  this->width = width;
  this->height = height;
  Calculate();
}

void Camera::SetZoom(float zoom) {
  this->zoom = zoom;
  Calculate();
}

void Camera::SetCenter(float x, float y) {
  this->center_x = x;
  this->center_y = y;
  Calculate();
}
void Camera::SetCenter(Point* center) {
  SetCenter(center->x, center->y);
}

void Camera::Calculate() {
  float extents_x = ((float)width / (float)height) * unit * zoom;
  float extents_y = unit * zoom;

  lower_x = center_x - extents_x;
  lower_y = center_y - extents_y;
  upper_x = center_x + extents_x;
  upper_y = center_y + extents_y;

  // x(0,1,2) 3
  matrix[0] = 2.0f / (upper_x - lower_x);
  matrix[1] = 0.0f;
  matrix[2] = 0.0f;
  matrix[3] = 0.0f;

  // y(4,5,6) 7
  matrix[4] = 0.0f;
  matrix[5] = 2.0f / (upper_y - lower_y);
  matrix[6] = 0.0f;
  matrix[7] = 0.0f;

  // z(8,9,10) 11
  matrix[8] = 0.0f;
  matrix[9] = 0.0f;
  matrix[10] = 1.0f;
  matrix[11] = 0.0f;

  // offset(12,13,14) 15
  matrix[12] = -(upper_x + lower_x) / (upper_x - lower_x);
  matrix[13] = -(upper_y + lower_y) / (upper_y - lower_y);
  matrix[14] = 0.0f;
  matrix[15] = 1.0f;
}

void Camera::BuildProjMatrix(float depth) { matrix[14] = depth; }

void Camera::ConvertScreenToWorld(float *x, float *y, const float screen_x,
                                  const float screen_y) {
  float u = screen_x / width;
  float v = (height - screen_y) / height;

  *x = (1.0f - u) * lower_x + u * upper_x;
  *y = (1.0f - v) * lower_y + v * upper_y;
}
void Camera::ConvertScreenToWorld(Point* p, Point* screen_p) {
  ConvertScreenToWorld(&p->x, &p->y, screen_p->x, screen_p->y);
}
void Camera::ConvertScreenToWorld(Point* p) {
  ConvertScreenToWorld(p, p);
}

void Camera::ConvertWorldToScreen(float *x, float *y, const float world_x,
                                  const float world_y) {
  float u = (world_x - lower_x) / (upper_x - lower_x);
  float v = (world_y - lower_y) / (upper_y - lower_y);

  *x = u * width;
  *y = (1.0f - v) * height;
}
void Camera::ConvertWorldToScreen(Point* p, Point* screen_p) {
  ConvertWorldToScreen(&p->x, &p->y, screen_p->x, screen_p->y);
}
void Camera::ConvertWorldToScreen(Point* p) {
  ConvertWorldToScreen(p, p);
}
} // namespace tkgl
} // namespace tkht
