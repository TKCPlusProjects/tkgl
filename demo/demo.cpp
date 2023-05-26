#include <tkcore/tkcore.hpp>
#include <tkgl/tkgl.hpp>

class RendererPoint : public tkgl::Renderer {
public:
  RendererPoint(shared_ptr<Camera> camera) : Renderer(camera, 0.1f, 1) {}

  void GLFlush() override {
    glEnable(GL_PROGRAM_POINT_SIZE);
    glDrawArrays(GL_POINTS, 0, shader->count);
    glDisable(GL_PROGRAM_POINT_SIZE);
  }
};

class RendererLine : public tkgl::Renderer {
public:
  RendererLine(shared_ptr<Camera> camera) : Renderer(camera, 0.1f, 2) {}

  void GLFlush() override {
    glDrawArrays(GL_LINES, 0, shader->count);
  }
};

class RendererTriangle : public tkgl::Renderer {
public:
  RendererTriangle(shared_ptr<Camera> camera) : Renderer(camera, 0.2f, 3) {}

  void GLFlush() override {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDrawArrays(GL_TRIANGLES, 0, shader->count);
    glDisable(GL_BLEND);
  }
};

int main() {
  Debug = true;
  SubscribeSignalCrash();

  if (!glfwInit()) {
    Assert(false, "GLFW Init Failed");
    return -1;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  float width = 1080.0f;
  float height = 720.0f;
  
  GLFWwindow* window = glfwCreateWindow(width, height, "Demo", nullptr, nullptr);
  if (!window) {
    glfwTerminate();
    Assert(false, "GLFW Create window Failed");
    return -1;
  }

  glfwMakeContextCurrent(window);
  glClearColor(0.9f, 0.9f, 0.9f, 1.0f);

  glewExperimental = GL_TRUE;
  glewInit();

  shared_ptr<Camera> camera = make_shared<Camera>(25.0f);
  camera->SetSize(width, height);

  shared_ptr<RendererPoint> renderer_point = make_shared<RendererPoint>(camera); 
  shared_ptr<RendererLine> renderer_line = make_shared<RendererLine>(camera);
  shared_ptr<RendererTriangle> renderer_triangle = make_shared<RendererTriangle>(camera);

  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();

    glClear(GL_COLOR_BUFFER_BIT);

    int count = 600;
    for (size_t i = 0; i < count; i++) {
      float offset = ((float)i - count/2) * 0.2f;
      renderer_point->Push(5.0f, 0.0f, 0.00f + offset, 0.0f, 0.0f, 0.0f, 1.0f);
    }
    renderer_point->Flush();

    for (size_t i = 0; i < count; i++) {
      float offset = ((float)i - count/2) * 0.2f;
      renderer_line->Push(1.0f, -5.0f, -5.00f + offset, 0.0f, 0.0f, 0.0f, 1.0f);
      renderer_line->Push(1.0f,  5.0f,  5.00f + offset, 0.0f, 0.0f, 0.0f, 1.0f);

      renderer_line->Push(1.0f, -5.0f,  5.00f + offset, 0.0f, 0.0f, 0.0f, 1.0f);
      renderer_line->Push(1.0f,  5.0f, -5.00f + offset, 0.0f, 0.0f, 0.0f, 1.0f);
    }
    renderer_line->Flush();

    for (size_t i = 0; i < count; i++) {
        float offset = ((float)i - count/2) * 0.2f;
        renderer_triangle->Push(1.0f, -1.0f, -1.00f + offset, 1.0f, 0.0f, 0.0f, 0.1f);
        renderer_triangle->Push(1.0f,  1.0f, -1.00f + offset, 1.0f, 0.0f, 0.0f, 0.1f);
        renderer_triangle->Push(1.0f,  0.0f,  1.00f + offset, 1.0f, 0.0f, 0.0f, 0.1f);
    }
    renderer_triangle->Flush();

    glfwSwapBuffers(window);
  }

  glfwDestroyWindow(window);
  glfwTerminate();

  return 1;
}