#include "dmp/TimeBubble.hpp"

#include <cmath>

namespace dmp {

namespace {
float distance(const Vec3& a, const Vec3& b) {
    const float dx = a.x - b.x;
    const float dy = a.y - b.y;
    const float dz = a.z - b.z;
    return std::sqrt(dx * dx + dy * dy + dz * dz);
}
} // namespace

void TimeBubbleSystem::createBubble(const TimeBubble& bubble) { bubbles_.push_back(bubble); }

float TimeBubbleSystem::timeScaleAt(const Vec3& position, std::uint64_t tick) const {
    float scale = 1.0F;
    for (const auto& bubble : bubbles_) {
        if (tick > bubble.expiresAtTick) {
            continue;
        }
        if (distance(position, bubble.center) <= bubble.radius) {
            scale = std::min(scale, bubble.scale);
        }
    }
    return scale;
}

} // namespace dmp
