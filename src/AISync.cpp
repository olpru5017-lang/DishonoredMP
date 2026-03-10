#include "dmp/AISync.hpp"

#include <cmath>

namespace dmp {

namespace {
float sqrDistance(const Vec3& a, const Vec3& b) {
    const float dx = a.x - b.x;
    const float dy = a.y - b.y;
    const float dz = a.z - b.z;
    return (dx * dx) + (dy * dy) + (dz * dz);
}
} // namespace

void AISync::updateFromStimuli(std::vector<AIState>& actors, const std::vector<PlayerState>& players) {
    for (auto& actor : actors) {
        actor.alert = AlertState::Relaxed;
        actor.suspicion = 0.0F;
        actor.targetNetId.reset();

        for (const auto& player : players) {
            const float dist2 = sqrDistance(player.transform.position, Vec3{});
            if (dist2 < 49.0F) {
                actor.alert = AlertState::Combat;
                actor.suspicion = 1.0F;
                actor.targetNetId = player.netId;
                actor.behavior = "EngageAndPursue";
                break;
            }
            if (dist2 < 225.0F) {
                actor.alert = AlertState::Suspicious;
                actor.suspicion = 0.65F;
                actor.targetNetId = player.netId;
                actor.behavior = "InvestigateSoundAndVision";
            }
        }
    }
}

} // namespace dmp
