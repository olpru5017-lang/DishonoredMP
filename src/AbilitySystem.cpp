#include "dmp/AbilitySystem.hpp"

namespace dmp {

void AbilitySystem::queueEvent(const AbilityEvent& event) { queue_.push_back(event); }

std::optional<AbilityEvent> AbilitySystem::popNext() {
    if (queue_.empty()) {
        return std::nullopt;
    }

    AbilityEvent next = queue_.front();
    queue_.pop_front();
    return next;
}

std::size_t AbilitySystem::pending() const noexcept { return queue_.size(); }

} // namespace dmp
