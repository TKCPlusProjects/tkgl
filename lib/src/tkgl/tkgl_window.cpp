#include <tkgl/tkgl_window.hpp>

namespace tkht
{
namespace tkgl
{
bool        Initialized = false;
GLFWwindow *RootWindow  = nullptr;

std::map<const char *, std::function<void(int width, int height)>> FramebufferSizeCallbackMap = {};
std::map<const char *, std::function<void(double offset_x, double offset_y)>> ScrollCallbackMap
  = {};
std::map<const char *, std::function<void(double x, double y)>> CursorPosCallbackMap = {};

float CurrentTime = 0.0f;

GLFWwindow *Window::Root() {
  return RootWindow;
}

int Window::Init(int width, int height, const char *title) {
  if (RootWindow == nullptr) {
    if (!glfwInit()) {
      Err("GLFW Init Failed");
      return GL_FALSE;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    RootWindow = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!RootWindow) {
      Err("GLFW Create Window Failed");
      return GL_FALSE;
    }
  } else {
    Msg("Window Already Initialized");
  }
  
  glfwMakeContextCurrent(RootWindow);
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    Err("GLAD Load Failed");
    return GL_FALSE;
  }

  glfwSetFramebufferSizeCallback(Root(), [](GLFWwindow *window, int width, int height) {
    for (const auto &pair : FramebufferSizeCallbackMap) {
      pair.second(width, height);
    }
  });
  glfwSetScrollCallback(Root(), [](GLFWwindow *window, double offset_x, double offset_y) {
    for (const auto &pair : ScrollCallbackMap) {
      pair.second(offset_x, offset_y);
    }
  });
  glfwSetCursorPosCallback(Root(), [](GLFWwindow *window, double x, double y) {
    for (const auto &pair : CursorPosCallbackMap) {
      pair.second(x, y);
    }
  });

  return GL_TRUE;
}

void Window::SetSizeCallback(
  const char *name, std::function<void(int width, int height)> callback
) {
  FramebufferSizeCallbackMap.insert(std::make_pair(name, callback));
}

void Window::RemoveSizeCallback(const char *name) {
  FramebufferSizeCallbackMap.erase(name);
}

void Window::SetScrollCallback(
  const char *name, std::function<void(double offset_x, double offset_y)> callback
) {
  ScrollCallbackMap.insert(std::make_pair(name, callback));
}

void Window::RemoveScrollCallback(const char *name) {
  ScrollCallbackMap.erase(name);
}

void Window::SetCursorCallback(
  const char *name, std::function<void(double x, double y)> callback
) {
  CursorPosCallbackMap.insert(std::make_pair(name, callback));
}

void Window::RemoveCursorCallback(const char *name) {
  CursorPosCallbackMap.erase(name);
}

void Window::Draw(std::function<void(float delta_time)> func) {
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  while (!glfwWindowShouldClose(RootWindow)) {
    glfwMakeContextCurrent(RootWindow);
    glfwPollEvents();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    float new_time   = static_cast<float>(glfwGetTime());
    float delta_time = new_time - CurrentTime;
    CurrentTime      = new_time;
    func(delta_time);
    
    glfwSwapBuffers(RootWindow);
  }
}

void Window::Terminate() {
  glfwDestroyWindow(RootWindow);
  glfwTerminate();
}
}
}