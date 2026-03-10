#include "dmp/Replication.hpp"

#include <cmath>

namespace dmp {

namespace {
float distance(const Vec3& a, const Vec3& b) {
    const float dx = a.x - b.x;
    const float dy = a.y - b.y;
    const float dz = a.z - b.z;
    return std::sqrt(dx * dx + dy * dy + dz * dz);
}

Vec3 interpolate(const Vec3& current, const Vec3& target, float alpha) {
    return {
        current.x + ((target.x - current.x) * alpha),
        current.y + ((target.y - current.y) * alpha),
        current.z + ((target.z - current.z) * alpha),
    };
}
} // namespace

ReplicationCoordinator::ReplicationCoordinator(Config config) : config_(std::move(config)) {}

void ReplicationCoordinator::applyHostSnapshot(const Snapshot& authoritative) {
    latest_ = authoritative;
    stats_.packetsSent += 1;
    stats_.bytesSent += (latest_.players.size() * sizeof(PlayerState));
}

PlayerState ReplicationCoordinator::reconcileRemotePlayer(const PlayerState& predicted, const PlayerState& authoritative) const {
    PlayerState merged = authoritative;
    const auto diff = distance(predicted.transform.position, authoritative.transform.position);

    if (diff > config_.snapThresholdMeters) {
        merged.transform.position = authoritative.transform.position;
    } else {
        merged.transform.position = interpolate(predicted.transform.position, authoritative.transform.position, config_.interpAlpha);
    }

    return merged;
}

std::vector<PlayerState> ReplicationCoordinator::distanceCull(const PlayerState& receiver,
                                                              const std::vector<PlayerState>& players) const {
    std::vector<PlayerState> relevant;
    relevant.reserve(players.size());

    constexpr float aoIRadius = 90.0F;
    for (const auto& player : players) {
        if (player.netId == receiver.netId || distance(receiver.transform.position, player.transform.position) <= aoIRadius) {
            relevant.push_back(player);
        }
    }

    return relevant;
}

const Snapshot& ReplicationCoordinator::latest() const noexcept { return latest_; }
const ReplicationStats& ReplicationCoordinator::stats() const noexcept { return stats_; }

} // namespace dmp
