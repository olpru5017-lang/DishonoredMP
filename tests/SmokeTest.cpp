#include "dmp/AbilitySystem.hpp"
#include "dmp/Config.hpp"
#include "dmp/MenuIntegration.hpp"
#include "dmp/Plugin.hpp"

#include <cassert>

int main() {
    dmp::Config cfg;
    dmp::DishonoredMPPlugin plugin(cfg);

    dmp::AbilityEvent bendTime;
    bendTime.ability = dmp::AbilityType::BendTime;
    bendTime.location = {0.0F, 0.0F, 0.0F};
    bendTime.radius = 10.0F;

    plugin.onAbilityRPC(bendTime);
    plugin.onHostTick(1);
    assert(plugin.snapshot().tick == 1);

    dmp::MenuIntegration menu;
    menu.ensureMultiplayerButton();
    menu.ensureMultiplayerButton();
    assert(menu.entries().size() == 1);
    assert(menu.entries().front().label == "Multiplayer");

    return 0;
}
