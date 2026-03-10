#pragma once

#include "dmp/NetworkTypes.hpp"

#include <deque>
#include <optional>

namespace dmp {

struct AbilityEvent {
    std::uint64_t tick{};
    std::uint32_t casterNetId{};
    AbilityType ability{AbilityType::Blink};
    Vec3 location{};
    float radius{};
};

class AbilitySystem {
  public:
    void queueEvent(const AbilityEvent& event);
    std::optional<AbilityEvent> popNext();
    [[nodiscard]] std::size_t pending() const noexcept;

  private:
    std::deque<AbilityEvent> queue_;
};

} // namespace dmp
