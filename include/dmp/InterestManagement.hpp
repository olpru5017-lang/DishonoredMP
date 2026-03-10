#pragma once

#include "dmp/NetworkTypes.hpp"

#include <vector>

namespace dmp {

class InterestManagement {
  public:
    std::vector<PlayerState> selectRelevantPlayers(const PlayerState& receiver, const std::vector<PlayerState>& allPlayers,
                                                   float maxDistanceMeters) const;
};

} // namespace dmp
