#include <tkgl/tkgl_graphic.hpp>

namespace tkht {
namespace tkgl {
void Graphic::Write() {
  ofstream file(path, ios::binary);
  if (!file.is_open()) {
    Err("读取资源文件失败"); return;
  }

  file.write((char*)&color.r, sizeof(float));
  file.write((char*)&color.g, sizeof(float));
  file.write((char*)&color.b, sizeof(float));
  file.write((char*)&color.a, sizeof(float));

  for (shared_ptr<Shape> shape : shapes) {
    file.write((char*)&shape->type, sizeof(float));
    shape->Write(&file);
  }

  file.close();
}

void Graphic::Read() {
  ifstream file(path, ios::binary);
  if (!file.is_open()) {
    Err("读取资源文件失败"); return;
  }

  file.read((char*)&color.r, sizeof(float));
  file.read((char*)&color.g, sizeof(float));
  file.read((char*)&color.b, sizeof(float));
  file.read((char*)&color.a, sizeof(float));

  while(true) {
    Shape::Type type;
    file.read((char*)&type, sizeof(float));
    switch (type) {
    case Shape::TypePoint: {
      shared_ptr<ShapePoint> shape = make_shared<ShapePoint>();
      shape->Read(&file);
      shapes.push_back(shape);
    } break;
    case Shape::TypeSegment: {
      shared_ptr<ShapeSegment> shape = make_shared<ShapeSegment>();
      shape->Read(&file);
      shapes.push_back(shape);
    } break;
    case Shape::TypePolygon: {
      shared_ptr<ShapePolygon> shape = make_shared<ShapePolygon>();
      shape->Read(&file);
      shapes.push_back(shape);
    } break;
    case Shape::TypeCircle: {
      shared_ptr<ShapeCircle> shape = make_shared<ShapeCircle>();
      shape->Read(&file);
      shapes.push_back(shape);
    } break;
    }
    if(file.eof()) break;
  }

  file.close();
}
} // namespace tkgl
} // namespace tkht
