#include <tkgl/tkgl_shape.hpp>

namespace tkht
{
namespace tkgl
{
const char* Shape::vs_unicolor
  = "#version 330\n"
    "layout(location = 0) in vec3 v_position;\n"
    "uniform mat4 projection;\n"
    "uniform mat4 view;\n"
    "uniform mat4 model;\n"
    "void main(void) {\n"
    "  gl_Position = projection * view * model * vec4(v_position, 1.0f);\n"
    "}\n";
const char* Shape::vs_multicolor
  = "#version 330\n"
    "layout(location = 0) in vec3 v_position;\n"
    "layout(location = 1) in vec4 v_color;\n"
    "uniform mat4 projection;\n"
    "uniform mat4 view;\n"
    "uniform mat4 model;\n"
    "out vec4 f_color;\n"
    "void main(void) {\n"
    "  gl_Position = projection * view * model * vec4(v_position, 1.0f);\n"
    "  f_color = v_color;\n"
    "}\n";
const char* Shape::fs_unicolor
  = "#version 330\n"
    "uniform vec4 color;\n"
    "out vec4 FragColor;\n"
    "void main(void) {\n"
    "  FragColor  = color;\n"
    "}\n";
const char* Shape::fs_multicolor
  = "#version 330\n"
    "in vec4 f_color;\n"
    "out vec4 FragColor;\n"
    "void main(void) {\n"
    "  FragColor  = f_color;\n"
    "}\n";

Shape::Shape(bool unicolor) :
  Shader(
    Shader::load_code(GL_VERTEX_SHADER, unicolor ? Shape::vs_unicolor : Shape::vs_multicolor),
    Shader::load_code(GL_FRAGMENT_SHADER, unicolor ? Shape::fs_unicolor : Shape::fs_multicolor)
  ),
  unicolor(unicolor) {
  if (unicolor) {
    generate({3});
  } else {
    generate({3, 4});
  }
}

void Shape::push(glm::vec3 vertex, glm::vec4 color) {
  pos_list.push_back(vertex);
  col_list.push_back(color);
}

void Shape::insert(GLuint index, glm::vec3 vertex, glm::vec4 color) {
  pos_list.insert(pos_list.begin() + index, vertex);
  col_list.insert(col_list.begin() + index, color);
}

void Shape::remove(GLuint index) {
  pos_list.erase(pos_list.begin() + index);
  col_list.erase(col_list.begin() + index);
}

void Shape::clear() {
  pos_list.clear();
  col_list.clear();
}

void Shape::buffer() {
  refresh();

  use();
  glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
  glBufferData(
    GL_ARRAY_BUFFER, pos_list.size() * sizeof(float) * 3, pos_list.data(), GL_STATIC_DRAW
  );
  if (unicolor) {
    set_vec4("color", color);
  } else {
    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferData(
      GL_ARRAY_BUFFER, col_list.size() * sizeof(float) * 4, col_list.data(), GL_STATIC_DRAW
    );
  }
}

void Shape::flush(std::shared_ptr<Camera> camera) {
  use();
  glm::mat4 projection = camera->get_projection_matrix();
  set_mat4("projection", projection);
  glm::mat4 view = camera->get_view_matrix();
  set_mat4("view", view);
  glm::mat4 model = glm::mat4(1.0f);
  set_mat4("model", model);
  render();
}
}
}