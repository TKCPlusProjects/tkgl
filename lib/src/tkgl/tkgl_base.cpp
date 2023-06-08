#include <tkgl/tkgl_base.hpp>

namespace tkht {
namespace tkgl {
float kCircleSegments = 16.0f;
float kCircleIncrement = 2.0f * kPI / kCircleSegments;
float kSinInc = sinf(kCircleIncrement);
float kCosInc = cosf(kCircleIncrement);

void SetCircleSegments(float v) {
  kCircleSegments = v;
  kCircleIncrement = 2.0f * kPI / kCircleSegments;
  kSinInc = sinf(kCircleIncrement);
  kCosInc = cosf(kCircleIncrement);
}
} // namespace tkgl
} // namespace tkht
