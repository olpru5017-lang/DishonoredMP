#include "dmp/ProxyAvatar.hpp"

#include <cmath>

namespace dmp {

NetworkPlayerProxyEntity::NetworkPlayerProxyEntity(std::uint32_t netId) : netId_(netId) { state_.netId = netId; }

void NetworkPlayerProxyEntity::attachNicknameBillboard(std::string nickname) { state_.nickname = std::move(nickname); }

void NetworkPlayerProxyEntity::updateFromRemote(const PlayerState& state) {
    state_ = state;
    state_.netId = netId_;
}

const PlayerState& NetworkPlayerProxyEntity::state() const noexcept { return state_; }

bool NetworkPlayerProxyEntity::isNicknameVisible(const Vec3& cameraPos, bool hasLineOfSight) const {
    if (!hasLineOfSight) {
        return false;
    }

    const float dx = state_.transform.position.x - cameraPos.x;
    const float dy = state_.transform.position.y - cameraPos.y;
    const float dz = state_.transform.position.z - cameraPos.z;
    const float distance = std::sqrt((dx * dx) + (dy * dy) + (dz * dz));
    return distance < 40.0F;
}

} // namespace dmp
