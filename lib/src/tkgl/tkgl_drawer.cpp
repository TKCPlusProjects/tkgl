#include <tkgl/tkgl_drawer.hpp>

namespace tkht {
namespace tkgl {
Drawer::Drawer(shared_ptr<Camera> camera, float depth) {
  point = make_shared<RendererPoint>(camera, depth);
  line = make_shared<RendererLine>(camera, depth);
  triangle = make_shared<RendererTriangle>(camera, depth);
}

void Drawer::DrawPoint(float size, Point* p, Color* color) {
  point->Push(size, p, color);
}

void Drawer::DrawSegment(Point* po, Point* pt, Color* color) {
  line->Push(po, color);
  line->Push(pt, color);
}

void Drawer::DrawPolygon(vector<Point> vertexes, Color* color) {
  Point po = vertexes.back();
  for (int i = 0; i < vertexes.size(); ++i) {
    Point pt = vertexes[i];
    line->Push(&po, color);
    line->Push(&pt, color);
    po = pt;
  }
}

void Drawer::DrawSolidPolygon(vector<Point> vertexes, Color* color) {
  for (int i = 1; i < vertexes.size() - 1; ++i) {
    triangle->Push(&vertexes[0], color);
    triangle->Push(&vertexes[i], color);
    triangle->Push(&vertexes[i + 1], color);
  }
  DrawPolygon(vertexes, color);
}

void Drawer::DrawCircle(Point* center, float radius, Color* color) {
  Point ro(1.0f, 0.0f);
  Point vo = *center + radius * ro;
  for (int i = 0; i < kCircleSegments; ++i) {
    Point rt(kCosInc * ro.x - kSinInc * ro.y, kSinInc * ro.x + kCosInc * ro.y);
    Point vt = *center + radius * rt;
    line->Push(&vo, color);
    line->Push(&vt, color);
    ro = rt;
    vo = vt;
  }
}

void Drawer::DrawSolidCircle(Point* center, float radius, Point* axis, Color* color) {
  Point ro(kCosInc, kSinInc);
  Point vo = *center + radius * ro;
  for (int i = 0; i < kCircleSegments; ++i) {
    Point rt(kCosInc * ro.x - kSinInc * ro.y, kSinInc * ro.x + kCosInc * ro.y);
    Point vt = *center + radius * rt;
    triangle->Push(center, color);
    triangle->Push(&vo, color);
    triangle->Push(&vt, color);
    ro = rt;
    vo = vt;
  }

  Point p = *center;
  if (axis) p = p + radius * *axis;
  line->Push(center, color);
  line->Push(&p, color);

  DrawCircle(center, radius, color);
}

void Drawer::DrawGraphic(Graphic* graphic) {
  for (shared_ptr<Shape> shape : graphic->shapes) {
    switch (shape->type) {
    case Shape::TypePoint: {
      shared_ptr<ShapePoint> type_shape = static_pointer_cast<ShapePoint>(shape);
      DrawPoint(type_shape->size, &type_shape->p, &graphic->color);
    } break;
    case Shape::TypeSegment: {
      shared_ptr<ShapeSegment> type_shape = static_pointer_cast<ShapeSegment>(shape);
      DrawSegment(&type_shape->o, &type_shape->t, &graphic->color);
    } break;
    case Shape::TypePolygon: {
      shared_ptr<ShapePolygon> type_shape = static_pointer_cast<ShapePolygon>(shape);
      if (type_shape->is_solid) {
        DrawSolidPolygon(type_shape->vertexes, &graphic->fillcolor);
      } else {
        DrawPolygon(type_shape->vertexes, &graphic->color);
      }
    } break;
    case Shape::TypeCircle: {
      shared_ptr<ShapeCircle> type_shape = static_pointer_cast<ShapeCircle>(shape);
      if (type_shape->is_solid) {
        DrawSolidCircle(&type_shape->center, type_shape->radius, nullptr, &graphic->fillcolor);
      } else {
        DrawCircle(&type_shape->center, type_shape->radius, &graphic->color);
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
