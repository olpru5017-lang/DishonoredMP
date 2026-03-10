#pragma once

#include "dmp/Config.hpp"
#include "dmp/NetworkTypes.hpp"

#include <cstdint>
#include <unordered_map>
#include <vector>

namespace dmp {

struct ReplicationStats {
    std::uint64_t packetsSent{};
    std::uint64_t bytesSent{};
};

class ReplicationCoordinator {
  public:
    explicit ReplicationCoordinator(Config config);

    void applyHostSnapshot(const Snapshot& authoritative);
    PlayerState reconcileRemotePlayer(const PlayerState& predicted, const PlayerState& authoritative) const;
    std::vector<PlayerState> distanceCull(const PlayerState& receiver, const std::vector<PlayerState>& players) const;

    [[nodiscard]] const Snapshot& latest() const noexcept;
    [[nodiscard]] const ReplicationStats& stats() const noexcept;

  private:
    Config config_;
    Snapshot latest_{};
    ReplicationStats stats_{};
};

} // namespace dmp
