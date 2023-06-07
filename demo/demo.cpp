#include <tkcore/tkcore.hpp>
#include <tkgl/tkgl.hpp>

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

  shared_ptr<Drawer> drawer = make_shared<Drawer>(camera, 0.0f);

  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();

    glClear(GL_COLOR_BUFFER_BIT);

    {
      Color color(1.0f, 0.0f, 0.0f, 1.0f);
      Point center(0.0f, 0.0f);
      drawer->DrawPoint(10.0f, &center, &color);
      Point po(-10.0f, 0.0f);
      Point pt( 10.0f, 0.0f);
      drawer->DrawSegment(&po, &pt, &color);
      vector<Point> vertexes({
        Point(-2.0f,  2.0f),
        Point( 2.0f,  2.0f),
        Point( 2.0f, -2.0f),
        Point(-2.0f, -2.0f),
      });
      drawer->DrawPolygon(vertexes, &color);
      drawer->DrawCircle(&center, 5.0f, &color);
    }

    {
      Color color(0.0f, 1.0f, 0.0f, 1.0f);
      vector<Point> vertexes({
        Point(-2.0f,  2.0f + 10.0f),
        Point( 2.0f,  2.0f + 10.0f),
        Point( 2.0f, -2.0f + 10.0f),
        Point(-2.0f, -2.0f + 10.0f),
      });
      drawer->DrawSolidPolygon(vertexes, &color);
      Point center(0.0f, -10.0f);
      Point axis(2.0f, 0.0f);
      drawer->DrawSolidCircle(&center, 5.0f, &axis, &color);
    }

    drawer->Flush();

    glfwSwapBuffers(window);
  }

  glfwDestroyWindow(window);
  glfwTerminate();

  return 1;
}