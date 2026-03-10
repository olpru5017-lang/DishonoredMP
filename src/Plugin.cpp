#include "dmp/Plugin.hpp"
#include "dmp/Logger.hpp"

#include <utility>

namespace dmp {

DishonoredMPPlugin::DishonoredMPPlugin(Config config)
    : config_(std::move(config)), replication_(config_) {
    hooks_.install({"TickHook", 0x1000, 0x2000, false});
    hooks_.install({"AbilityHook", 0x1100, 0x2100, false});
    hooks_.install({"MainMenuHook", 0x1200, 0x2200, false});
    Logger::instance().info("DishonoredMPPlugin initialized with crash-safe detours");
}

void DishonoredMPPlugin::onHostTick(std::uint64_t tick) {
    simulation_.tick = tick;
    aiSync_.updateFromStimuli(simulation_.aiActors, simulation_.players);

    while (const auto event = abilities_.popNext()) {
        if (event->ability == AbilityType::BendTime) {
            timeBubble_.createBubble({event->location, event->radius, 0.35F, tick + 240});
        }
    }

    replication_.applyHostSnapshot(simulation_);
}

void DishonoredMPPlugin::onClientPrediction(std::uint64_t, const PlayerState& predictedLocal) {
    if (simulation_.players.empty()) {
        simulation_.players.push_back(predictedLocal);
        return;
    }

    simulation_.players[0] = replication_.reconcileRemotePlayer(predictedLocal, simulation_.players[0]);
}

void DishonoredMPPlugin::onAbilityRPC(const AbilityEvent& event) { abilities_.queueEvent(event); }

void DishonoredMPPlugin::onMainMenuFrame() {
    menu_.ensureMultiplayerButton();
}

void DishonoredMPPlugin::addOrUpdateProxy(const PlayerState& remoteState) {
    auto [it, inserted] = proxies_.try_emplace(remoteState.netId, remoteState.netId);
    it->second.attachNicknameBillboard(remoteState.nickname);
    it->second.updateFromRemote(remoteState);

    if (inserted) {
        Logger::instance().info("Created NetworkPlayerProxyEntity for netId=" + std::to_string(remoteState.netId));
    }
}

const Snapshot& DishonoredMPPlugin::snapshot() const noexcept { return replication_.latest(); }

} // namespace dmp
