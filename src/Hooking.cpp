#include "dmp/Hooking.hpp"

namespace dmp {

bool HookManager::install(HookRecord record) {
    record.installed = true;
    hooks_.push_back(record);
    return true;
}

void HookManager::removeAll() {
    for (auto& hook : hooks_) {
        hook.installed = false;
    }
}

const std::vector<HookRecord>& HookManager::hooks() const noexcept { return hooks_; }

} // namespace dmp
