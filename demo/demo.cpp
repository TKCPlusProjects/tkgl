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

  tkgl::SetCircleSegments(30.0f);

  shared_ptr<Camera> camera = make_shared<Camera>(25.0f);
  camera->SetSize(width, height);
  camera->SetZoom(0.5f);

  shared_ptr<Drawer> drawer = make_shared<Drawer>(camera, 0.0f);
  
  shared_ptr<Graphic> graphic = make_shared<Graphic>();
  graphic->path = "a1.tkgp";
  if (filesystem::exists(graphic->path)) {
    graphic->Read();
  } else {
    // graphic->color = Color(1.0f, 0.0f, 0.0f, 1.0f);
    // graphic->shapes.push_back(make_shared<ShapePoint>(10.0f, Point(0.0f, 0.0f)));
    // graphic->shapes.push_back(make_shared<ShapeSegment>(Point(0.0f, -10.0f), Point(0.0f,  10.0f)));
    // graphic->shapes.push_back(make_shared<ShapePolygon>(vector<Point>{
    //   Point(-1.0f,  1.0f),
    //   Point( 1.0f,  1.0f),
    //   Point( 1.0f, -1.0f),
    //   Point(-1.0f, -1.0f),
    // }));
    // graphic->shapes.push_back(make_shared<ShapeCircle>(Point(0.0f, 0.0f), 1.0f));
    // graphic->Write();
  }

  shared_ptr<Graphic> graphic_solid = make_shared<Graphic>();
  graphic_solid->path = "b1.tkgp";
  if (filesystem::exists(graphic_solid->path)) {
    graphic_solid->Read();
  } else {
    // graphic_solid->color = Color(0.0f, 1.0f, 0.0f, 1.0f);
    // graphic_solid->fillcolor = Color(0.0f, 0.5f, 0.0f, 0.5f);
    // graphic_solid->shapes.push_back(make_shared<ShapePolygon>(vector<Point>{
    //   Point(-1.0f,  1.0f + 5.0f),
    //   Point( 1.0f,  1.0f + 5.0f),
    //   Point( 1.0f, -1.0f + 5.0f),
    //   Point(-1.0f, -1.0f + 5.0f),
    // }, true));
    // graphic_solid->shapes.push_back(make_shared<ShapeCircle>(Point(0.0f, -5.0f), 1.0f, true));
    // graphic_solid->Write();
  }

  Transform transform(Point(), Rotation(0.02f));

  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();

    glClear(GL_COLOR_BUFFER_BIT);

    drawer->DrawGraphic(graphic.get(), &transform);
    drawer->DrawGraphic(graphic_solid.get(), &transform);

    drawer->Flush();

    glfwSwapBuffers(window);
  }

  glfwDestroyWindow(window);
  glfwTerminate();

  return 1;
}