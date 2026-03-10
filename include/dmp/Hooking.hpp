#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace dmp {

struct HookRecord {
    std::string name;
    std::uintptr_t targetAddress{};
    std::uintptr_t detourAddress{};
    bool installed{};
};

class HookManager {
  public:
    bool install(HookRecord record);
    void removeAll();
    [[nodiscard]] const std::vector<HookRecord>& hooks() const noexcept;

  private:
    std::vector<HookRecord> hooks_;
};

} // namespace dmp
