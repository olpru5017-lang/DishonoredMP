#pragma once

#include "dmp/NetworkTypes.hpp"

#include <string>

namespace dmp {

class NetworkPlayerProxyEntity {
  public:
    explicit NetworkPlayerProxyEntity(std::uint32_t netId);

    void attachNicknameBillboard(std::string nickname);
    void updateFromRemote(const PlayerState& state);
    [[nodiscard]] const PlayerState& state() const noexcept;
    [[nodiscard]] bool isNicknameVisible(const Vec3& cameraPos, bool hasLineOfSight) const;

  private:
    std::uint32_t netId_{};
    PlayerState state_{};
};

} // namespace dmp
