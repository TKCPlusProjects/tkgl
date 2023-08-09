/// @file tkgl_graphic.hpp
#ifndef tkgl_graphic_hpp
#define tkgl_graphic_hpp

#include <tkgl/tkgl_base.hpp>
#include <tkgl/tkgl_shape.hpp>
#include <tkgl/tkgl_shape_segment.hpp>
#include <tkgl/tkgl_shape_axis.hpp>
#include <tkgl/tkgl_shape_grid.hpp>
#include <tkgl/tkgl_shape_fan.hpp>
#include <tkgl/tkgl_shape_strip.hpp>
#include <tkgl/tkgl_shape_circle.hpp>
#include <tkgl/tkgl_shape_quad.hpp>

namespace tkht
{
namespace tkgl
{
/// @brief 图像
class Graphic {
public:
  std::string                         path;        ///< 路径
  std::shared_ptr<std::ofstream>      ofs;         ///< 输出文件流
  std::shared_ptr<std::ifstream>      ifs;         ///< 输入文件流
  std::vector<std::shared_ptr<Shape>> shape_list;  ///< 形状列表

  bool exists();
  void write();
  void read();
};
}
}
#endif
