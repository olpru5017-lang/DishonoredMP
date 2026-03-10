#pragma once

#include "dmp/AISync.hpp"
#include "dmp/AbilitySystem.hpp"
#include "dmp/Config.hpp"
#include "dmp/InterestManagement.hpp"
#include "dmp/MenuIntegration.hpp"
#include "dmp/Hooking.hpp"
#include "dmp/ProxyAvatar.hpp"
#include "dmp/Replication.hpp"
#include "dmp/TimeBubble.hpp"

#include <cstdint>
#include <unordered_map>

namespace dmp {

class DishonoredMPPlugin {
  public:
    explicit DishonoredMPPlugin(Config config);

    void onHostTick(std::uint64_t tick);
    void onClientPrediction(std::uint64_t tick, const PlayerState& predictedLocal);
    void onAbilityRPC(const AbilityEvent& event);
    void onMainMenuFrame();

    void addOrUpdateProxy(const PlayerState& remoteState);
    [[nodiscard]] const Snapshot& snapshot() const noexcept;

  private:
    Config config_;
    ReplicationCoordinator replication_;
    AbilitySystem abilities_;
    AISync aiSync_;
    InterestManagement interest_;
    TimeBubbleSystem timeBubble_;
    HookManager hooks_;
    MenuIntegration menu_;
    std::unordered_map<std::uint32_t, NetworkPlayerProxyEntity> proxies_;
    Snapshot simulation_{};
};

} // namespace dmp
