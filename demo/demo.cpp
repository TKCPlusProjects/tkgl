#include <tkgl/tkgl.hpp>

int main() {
  using namespace tkht;
  using namespace tkht::tkgl;

  Debug = true;
  SubscribeSignalList({SIGSEGV, SIGABRT});

  // init
  if (!Window::Init(800, 600, "Demo")) {
    return -1;
  }

  // monitor
  GLFWmonitor*       primaryMonitor = glfwGetPrimaryMonitor();
  const GLFWvidmode* videoMode      = glfwGetVideoMode(primaryMonitor);

  // camera
  std::shared_ptr<Camera> camera = std::make_shared<Camera>();
  camera->position  = glm::vec3(3.0f, 3.0f, 3.0f);
  camera->yaw      -= 45;
  camera->pitch    -= 45;
  camera->update();
  camera->get_viewport(videoMode->width, videoMode->height);

  // set callback
  Window::SetSizeCallback("Demo", [=](int width, int height) {
    Camera::Viewport viewport = camera->get_viewport(width, height);
    glViewport(viewport.x, viewport.y, viewport.width, viewport.height);
  });
  Window::SetScrollCallback("Demo", [=](double offset_x, double offset_y) {
    camera->process_mouse_scroll(offset_y);
  });
  Window::SetCursorCallback("Demo", [=](double x, double y) {
    camera->process_mouse_focus(x, y);
  });

  // set window rect
  glfwSetWindowPos(Window::Root(), camera->viewport.x, camera->viewport.y);
  glfwSetWindowSize(Window::Root(), camera->viewport.width, camera->viewport.height);

  // set input mode
  glfwSetInputMode(Window::Root(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  // polygon mode
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  // depth test
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // renderer
  std::shared_ptr<Graphic> graphic = std::make_shared<Graphic>();
  graphic->path                    = "demo.tkg";
  if (graphic->exists()) {
    graphic->read();
  } else {
    std::shared_ptr<ShapeAxis> shape_axis = std::make_shared<ShapeAxis>();
    shape_axis->set_radius(5.0f);
    shape_axis->buffer();

    std::shared_ptr<ShapeGrid> shape_grid = std::make_shared<ShapeGrid>();
    shape_grid->color                     = glm::vec4(0.5f);
    shape_grid->axis.rotate(shape_grid->axis.z, glm::vec3(0, 1.0f, 0));
    shape_grid->set_radius(5.0f);
    shape_grid->set_density(5.0f);
    shape_grid->buffer();

    std::shared_ptr<ShapeFan> shape_fan = std::make_shared<ShapeFan>();
    shape_fan->color                    = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
    shape_fan->pos_list              = {
      glm::vec3(+1.0f, +0.0f, +0.0f),
      glm::vec3(+0.7f, +0.0f, +0.7f),
      glm::vec3(+0.0f, +0.0f, +1.0f),
      glm::vec3(-0.7f, +0.0f, +0.7f),
      glm::vec3(-1.0f, +0.0f, +0.0f),
      glm::vec3(-0.7f, +0.0f, -0.7f),
      glm::vec3(+0.0f, +0.0f, -1.0f),
      glm::vec3(+0.7f, +0.0f, -0.7f),
    };
    shape_fan->buffer();

    std::shared_ptr<ShapeStrip> shape_strip = std::make_shared<ShapeStrip>();
    shape_strip->color                      = glm::vec4(1.0f);
    shape_strip->pos_list                = {
      glm::vec3(+1.0f, -0.1f, +0.0f),
      glm::vec3(+1.0f, +0.1f, +0.0f),
      glm::vec3(+0.7f, -0.1f, +0.7f),
      glm::vec3(+0.7f, +0.1f, +0.7f),
      glm::vec3(+0.0f, -0.1f, +1.0f),
      glm::vec3(+0.0f, +0.1f, +1.0f),
      glm::vec3(-0.7f, -0.1f, +0.7f),
      glm::vec3(-0.7f, +0.1f, +0.7f),
      glm::vec3(-1.0f, -0.1f, +0.0f),
      glm::vec3(-1.0f, +0.1f, +0.0f),
      glm::vec3(-0.7f, -0.1f, -0.7f),
      glm::vec3(-0.7f, +0.1f, -0.7f),
      glm::vec3(+0.0f, -0.1f, -1.0f),
      glm::vec3(+0.0f, +0.1f, -1.0f),
      glm::vec3(+0.7f, -0.1f, -0.7f),
      glm::vec3(+0.7f, +0.1f, -0.7f),
      glm::vec3(+1.0f, -0.1f, +0.0f),
      glm::vec3(+1.0f, +0.1f, +0.0f),
    };
    shape_strip->buffer();

    std::shared_ptr<ShapeCircle> shape_circle = std::make_shared<ShapeCircle>();
    shape_circle->buffer();

    std::shared_ptr<ShapeQuad> shape_quad = std::make_shared<ShapeQuad>();
    shape_quad->color                     = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
    shape_quad->axis.rotate(shape_quad->axis.z, glm::vec3(0, 1.0f, 0));
    shape_quad->set_radius(1.5f);
    shape_quad->buffer();

    graphic->shape_list.push_back(shape_axis);
    graphic->shape_list.push_back(shape_grid);
    graphic->shape_list.push_back(shape_fan);
    graphic->shape_list.push_back(shape_strip);
    graphic->shape_list.push_back(shape_circle);
    graphic->shape_list.push_back(shape_quad);
    graphic->write();
  }

  // drarw
  Window::Draw([=](float delta_time) {
    if (glfwGetKey(Window::Root(), GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      glfwSetWindowShouldClose(Window::Root(), true);
    }

    if (glfwGetKey(Window::Root(), GLFW_KEY_W) == GLFW_PRESS) {
      camera->process_movement(Camera::Movement::FORWARD, delta_time);
    }
    if (glfwGetKey(Window::Root(), GLFW_KEY_S) == GLFW_PRESS) {
      camera->process_movement(Camera::Movement::BACKWARD, delta_time);
    }
    if (glfwGetKey(Window::Root(), GLFW_KEY_A) == GLFW_PRESS) {
      camera->process_movement(Camera::Movement::LEFT, delta_time);
    }
    if (glfwGetKey(Window::Root(), GLFW_KEY_D) == GLFW_PRESS) {
      camera->process_movement(Camera::Movement::RIGHT, delta_time);
    }
    if (glfwGetKey(Window::Root(), GLFW_KEY_SPACE) == GLFW_PRESS) {
      camera->process_movement(Camera::Movement::UP, delta_time);
    }
    if (glfwGetKey(Window::Root(), GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
      camera->process_movement(Camera::Movement::DOWN, delta_time);
    }

    if (glfwGetKey(Window::Root(), GLFW_KEY_UP) == GLFW_PRESS) {
      camera->process_mouse_movement(0, +10.0f);
    }
    if (glfwGetKey(Window::Root(), GLFW_KEY_DOWN) == GLFW_PRESS) {
      camera->process_mouse_movement(0, -10.0f);
    }
    if (glfwGetKey(Window::Root(), GLFW_KEY_LEFT) == GLFW_PRESS) {
      camera->process_mouse_movement(-10.0f, 0);
    }
    if (glfwGetKey(Window::Root(), GLFW_KEY_RIGHT) == GLFW_PRESS) {
      camera->process_mouse_movement(+10.0f, 0);
    }

    for (std::shared_ptr<Shape> shape : graphic->shape_list) {
      shape->flush(camera);
    }
  });

  // terminate
  Window::Terminate();
  return 0;
}
