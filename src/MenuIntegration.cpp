#include "dmp/MenuIntegration.hpp"

#include <algorithm>

namespace dmp {

void MenuIntegration::ensureMultiplayerButton() {
    const auto it = std::find_if(entries_.begin(), entries_.end(), [](const MainMenuEntry& entry) {
        return entry.id == "dishonored_mp.multiplayer";
    });

    if (it == entries_.end()) {
        entries_.push_back({"dishonored_mp.multiplayer", "Multiplayer", 35});
    }
}

const std::vector<MainMenuEntry>& MenuIntegration::entries() const noexcept { return entries_; }

} // namespace dmp
