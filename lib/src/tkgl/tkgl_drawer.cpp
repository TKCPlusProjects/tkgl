#include <tkgl/tkgl_drawer.hpp>

namespace tkht {
namespace tkgl {
Drawer::Drawer(shared_ptr<Camera> camera, float depth) {
  point = make_shared<RendererPoint>(camera, depth);
  line = make_shared<RendererLine>(camera, depth);
  triangle = make_shared<RendererTriangle>(camera, depth);
}

void Drawer::DrawPoint(float size, Point* vertex, int count, Color* color) {
  for (int i = 0; i < count; ++i) {
    point->Push(size, &vertex[i], color);
  }
}
void Drawer::DrawSegment(Point* vertex, int count, Color* color) {
  for (int i = 0; i < count - 1; ++i) {
    line->Push(&vertex[i], color);
    line->Push(&vertex[++i], color);
  }
}
void Drawer::DrawContinueSegment(Point* vertex, int count, Color* color) {
  for (int i = 0; i < count - 1;) {
    line->Push(&vertex[i], color);
    line->Push(&vertex[++i], color);
  }
}
void Drawer::DrawPolygon(Point* vertex, int count, Color* color) {
  Point po = vertex[count - 1];
  for (int i = 0; i < count; ++i) {
    Point pt = vertex[i];
    line->Push(&po, color);
    line->Push(&pt, color);
    po = pt;
  }
}
void Drawer::DrawSolidPolygon(Point* vertex, int count, Color* color) {
  for (int i = 1; i < count - 1; ++i) {
    triangle->Push(&vertex[0], color);
    triangle->Push(&vertex[i], color);
    triangle->Push(&vertex[i + 1], color);
  }
  DrawPolygon(vertex, count, color);
}
void Drawer::DrawCircle(Point* center, float r, Color* color) {
  Point ro(1.0f, 0.0f);
  Point vo = *center + r * ro;
  for (int i = 0; i < kCircleSegments; ++i) {
    Point rt(kCosInc * ro.x - kSinInc * ro.y, kSinInc * ro.x + kCosInc * ro.y);
    Point vt = *center + r * rt;
    line->Push(&vo, color);
    line->Push(&vt, color);
    ro = rt;
    vo = vt;
  }
}
void Drawer::DrawSolidCircle(Point* center, float r, Point* axis, Color* color) {
  Point ro(kCosInc, kSinInc);
  Point vo = *center + r * ro;
  for (int i = 0; i < kCircleSegments; ++i) {
    Point rt(kCosInc * ro.x - kSinInc * ro.y, kSinInc * ro.x + kCosInc * ro.y);
    Point vt = *center + r * rt;
    triangle->Push(center, color);
    triangle->Push(&vo, color);
    triangle->Push(&vt, color);
    ro = rt;
    vo = vt;
  }

  Point p = *center;
  if (axis) p = p + r * *axis;
  line->Push(center, color);
  line->Push(&p, color);

  DrawCircle(center, r, color);
}

void Drawer::DrawGraphic(Graphic* graphic, Transform* transform) {
  for (shared_ptr<Shape> shape : graphic->shapes) {
    switch (shape->type) {
    case Shape::TypePoint: {
      shared_ptr<ShapePoint> type_shape = static_pointer_cast<ShapePoint>(shape);
      if (transform) {
        vector<Point> vertexes = type_shape->vertexes;
        for (size_t i = 0; i < vertexes.size(); i++) {
          vertexes[i] = Mul(*transform, vertexes[i]);
        }
        DrawPoint(type_shape->size, vertexes.data(), vertexes.size(), &graphic->color);
      } else {
        DrawPoint(type_shape->size, type_shape->vertexes.data(), type_shape->vertexes.size(), &graphic->color);
      }
    } break;
    case Shape::TypeSegment: {
      shared_ptr<ShapeSegment> type_shape = static_pointer_cast<ShapeSegment>(shape);
      if (transform) {
        vector<Point> vertexes = type_shape->vertexes;
        for (size_t i = 0; i < vertexes.size(); i++) {
          vertexes[i] = Mul(*transform, vertexes[i]);
        }
        if (type_shape->is_continue) {
          DrawContinueSegment(vertexes.data(), vertexes.size(), &graphic->color);
        } else {
          DrawSegment(vertexes.data(), vertexes.size(), &graphic->color);
        }
      } else {
        if (type_shape->is_continue) {
          DrawContinueSegment(type_shape->vertexes.data(), type_shape->vertexes.size(), &graphic->color);
        } else {
          DrawSegment(type_shape->vertexes.data(), type_shape->vertexes.size(), &graphic->color);
        }
      }

    } break;
    case Shape::TypePolygon: {
      shared_ptr<ShapePolygon> type_shape = static_pointer_cast<ShapePolygon>(shape);
      if (transform) {
        vector<Point> vertexes = type_shape->vertexes;
        for (size_t i = 0; i < vertexes.size(); i++) {
          vertexes[i] = Mul(*transform, vertexes[i]);
        }
        if (type_shape->is_solid) {
          DrawSolidPolygon(vertexes.data(), vertexes.size(), &graphic->fillcolor);
        } else {
          DrawPolygon(vertexes.data(), vertexes.size(), &graphic->color);
        }
      } else {
        if (type_shape->is_solid) {
          DrawSolidPolygon(type_shape->vertexes.data(), type_shape->vertexes.size(), &graphic->fillcolor);
        } else {
          DrawPolygon(type_shape->vertexes.data(), type_shape->vertexes.size(), &graphic->color);
        }
      }
    } break;
    case Shape::TypeCircle: {
      shared_ptr<ShapeCircle> type_shape = static_pointer_cast<ShapeCircle>(shape);
      if (transform) {
        Point center = Mul(*transform, type_shape->center);
        if (type_shape->is_solid) {
          DrawSolidCircle(&center, type_shape->r, nullptr, &graphic->fillcolor);
        } else {
          DrawCircle(&center, type_shape->r, &graphic->color);
        }
      } else {
        if (type_shape->is_solid) {
          DrawSolidCircle(&type_shape->center, type_shape->r, nullptr, &graphic->fillcolor);
        } else {
          DrawCircle(&type_shape->center, type_shape->r, &graphic->color);
        }
      }
    } break;
    }
  }
}

void Drawer::Flush() { 
  point->Flush();
  line->Flush();
  triangle->Flush();
}
} // namespace tkgl
} // namespace tkht
