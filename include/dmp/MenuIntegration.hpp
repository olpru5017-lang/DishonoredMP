#pragma once

#include <string>
#include <vector>

namespace dmp {

struct MainMenuEntry {
    std::string id;
    std::string label;
    int sortOrder{};
};

class MenuIntegration {
  public:
    void ensureMultiplayerButton();
    [[nodiscard]] const std::vector<MainMenuEntry>& entries() const noexcept;

  private:
    std::vector<MainMenuEntry> entries_;
};

} // namespace dmp
