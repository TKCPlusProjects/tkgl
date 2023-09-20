#include <boost/test/unit_test.hpp>

#include <tkgl/tkgl.hpp>

BOOST_AUTO_TEST_CASE(tkgl_test_axis_cache) {
  using namespace tkht;
  using namespace tkht::tkgl;

  Debug = true;

  const char* path = "axis.tkg";

  Axis axis_o;
  axis_o.set_position(glm::vec3(1.0f));
  axis_o.set_rotation(glm::vec3(90.0f));
  std::shared_ptr<std::ofstream> ofs = std::make_shared<std::ofstream>(path, std::ios::binary);
  if (ofs->is_open()) {
    ofs->write((char*)&axis_o, sizeof(Axis));
    ofs->close();
  } else {
    BOOST_ERROR("输出文件流打开失败");
  }

  Axis axis_i;
  std::shared_ptr<std::ifstream> ifs = std::make_shared<std::ifstream>(path, std::ios::binary);
  if (ifs->is_open()) {
    ifs->read((char*)&axis_i, sizeof(Axis));
    ifs->close();
  } else {
    BOOST_ERROR("输入文件流打开失败");
  }

  BOOST_TEST(glm::distance(axis_o.position, axis_i.position) < 1e-6);
  BOOST_TEST(glm::distance(axis_o.rotation, axis_i.rotation) < 1e-6);
  BOOST_TEST(glm::distance(axis_o.x, axis_i.x) < 1e-6);
  BOOST_TEST(glm::distance(axis_o.y, axis_i.y) < 1e-6);
  BOOST_TEST(glm::distance(axis_o.z, axis_i.z) < 1e-6);
}

BOOST_AUTO_TEST_CASE(tkgl_test_axis_r90) {
  using namespace tkht;
  using namespace tkht::tkgl;

  Debug = true;

  Axis axis;
  axis.rotate(glm::vec3(1.0f, 0, 0), glm::vec3(0.0f, 1.0f, 0));
  
  BOOST_TEST(glm::distance(axis.position, glm::vec3(0)) < 1e-6);
  BOOST_TEST(glm::distance(axis.rotation, glm::vec3(0, 0, 90.0f)) < 1e-6);
  BOOST_TEST(glm::distance(axis.x, glm::vec3(0, 1.0f, 0)) < 1e-6);
  BOOST_TEST(glm::distance(axis.y, glm::vec3(-1.0f, 0, 0)) < 1e-6);
  BOOST_TEST(glm::distance(axis.z, glm::vec3(0, 0, 1.0f)) < 1e-6);
}

BOOST_AUTO_TEST_CASE(tkgl_test_axis_r180) {
  using namespace tkht;
  using namespace tkht::tkgl;

  Debug = true;

  Axis axis;
  axis.rotate(glm::vec3(1.0f, 0, 0), glm::vec3(-1.0f, 0.0f, 0));

  BOOST_TEST(glm::distance(axis.position, glm::vec3(0)) < 1e-6);
  BOOST_TEST(glm::distance(axis.rotation, glm::vec3(0, 0, 180.0f)) < 1e-6);
  BOOST_TEST(glm::distance(axis.x, glm::vec3(-1.0f, 0, 0)) < 1e-6);
  BOOST_TEST(glm::distance(axis.y, glm::vec3(0, -1.0f, 0)) < 1e-6);
  BOOST_TEST(glm::distance(axis.z, glm::vec3(0, 0, 1.0f)) < 1e-6);
}
