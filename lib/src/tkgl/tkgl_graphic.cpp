#include <tkgl/tkgl_graphic.hpp>

namespace tkht
{
namespace tkgl
{
enum ShapeType : int {
  NONE = 0,
  SEGMENT,
  AXIS,
  GRID,
  FAN,
  STRIP,
  CIRCLE,
  QUAD,
};

bool Graphic::exists() {
  return std::filesystem::exists(path);
}

void Graphic::write() {
  ofs = std::make_shared<std::ofstream>(path, std::ios::binary);
  if (!ofs->is_open()) {
    Err("输出文件流打开失败 %s", path.c_str());
    return;
  }

  int count = (int)shape_list.size();
  ofs->write((char*)&count, sizeof(int));
  for (std::shared_ptr<Shape> shape : shape_list) {
    ShapeType type = NONE;
    if (false) {
    } else if (std::shared_ptr<ShapeSegment> type_shape = std::dynamic_pointer_cast<ShapeSegment>(shape)) {
      type = SEGMENT;
    } else if (std::shared_ptr<ShapeAxis> type_shape = std::dynamic_pointer_cast<ShapeAxis>(shape)) {
      type = AXIS;
    } else if (std::shared_ptr<ShapeGrid> type_shape = std::dynamic_pointer_cast<ShapeGrid>(shape)) {
      type = GRID;
    } else if (std::shared_ptr<ShapeFan> type_shape = std::dynamic_pointer_cast<ShapeFan>(shape)) {
      type = FAN;
    } else if (std::shared_ptr<ShapeStrip> type_shape = std::dynamic_pointer_cast<ShapeStrip>(shape)) {
      type = STRIP;
    } else if (std::shared_ptr<ShapeCircle> type_shape = std::dynamic_pointer_cast<ShapeCircle>(shape)) {
      type = CIRCLE;
    } else if (std::shared_ptr<ShapeQuad> type_shape = std::dynamic_pointer_cast<ShapeQuad>(shape)) {
      type = QUAD;
    }
    ofs->write((char*)&type, sizeof(ShapeType));
    shape->write(ofs);
  }

  ofs->close();
}

void Graphic::read() {
  ifs = std::make_shared<std::ifstream>(path, std::ios::binary);
  if (!ifs->is_open()) {
    Err("输入文件流打开失败 %s", path.c_str());
    return;
  }

  int count;
  ifs->read((char*)&count, sizeof(int));
  for (size_t i = 0; i < count; i++) {
    ShapeType type = NONE;
    ifs->read((char*)&type, sizeof(ShapeType));
    std::shared_ptr<Shape> type_shape = nullptr;
    switch (type) {
    case NONE: {
    } break;
    case SEGMENT: {
      type_shape = std::make_shared<ShapeSegment>();
    } break;
    case AXIS: {
      type_shape = std::make_shared<ShapeAxis>();
    } break;
    case GRID: {
      type_shape = std::make_shared<ShapeGrid>();
    } break;
    case FAN: {
      type_shape = std::make_shared<ShapeFan>();
    } break;
    case STRIP: {
      type_shape = std::make_shared<ShapeStrip>();
    } break;
    case CIRCLE: {
      type_shape = std::make_shared<ShapeCircle>();
    } break;
    case QUAD: {
      type_shape = std::make_shared<ShapeQuad>();
    } break;
    }
    type_shape->read(ifs);
    type_shape->buffer();
    shape_list.push_back(type_shape);
  }

  ifs->close();
}
}
}