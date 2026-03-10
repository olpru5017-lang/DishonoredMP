#pragma once

#include "dmp/NetworkTypes.hpp"

#include <vector>

namespace dmp {

class AISync {
  public:
    void updateFromStimuli(std::vector<AIState>& actors, const std::vector<PlayerState>& players);
};

} // namespace dmp
