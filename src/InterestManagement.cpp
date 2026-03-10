#include "dmp/InterestManagement.hpp"

#include <algorithm>
#include <cmath>

namespace dmp {

namespace {
float distance(const Vec3& a, const Vec3& b) {
    const float dx = a.x - b.x;
    const float dy = a.y - b.y;
    const float dz = a.z - b.z;
    return std::sqrt(dx * dx + dy * dy + dz * dz);
}
} // namespace

std::vector<PlayerState> InterestManagement::selectRelevantPlayers(const PlayerState& receiver,
                                                                    const std::vector<PlayerState>& allPlayers,
                                                                    float maxDistanceMeters) const {
    std::vector<PlayerState> selected;
    for (const auto& player : allPlayers) {
        if (player.netId == receiver.netId || distance(receiver.transform.position, player.transform.position) < maxDistanceMeters) {
            selected.push_back(player);
        }
    }

    std::sort(selected.begin(), selected.end(), [&](const PlayerState& a, const PlayerState& b) {
        return distance(receiver.transform.position, a.transform.position) < distance(receiver.transform.position, b.transform.position);
    });

    return selected;
}

} // namespace dmp
