#pragma once

#include "dmp/NetworkTypes.hpp"

#include <vector>

namespace dmp {

struct TimeBubble {
    Vec3 center{};
    float radius{};
    float scale{1.0F};
    std::uint64_t expiresAtTick{};
};

class TimeBubbleSystem {
  public:
    void createBubble(const TimeBubble& bubble);
    float timeScaleAt(const Vec3& position, std::uint64_t tick) const;

  private:
    std::vector<TimeBubble> bubbles_;
};

} // namespace dmp
