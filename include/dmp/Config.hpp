#pragma once

#include <cstdint>
#include <string>

namespace dmp {

struct Config {
    std::uint16_t port{30777};
    std::uint16_t tickRate{60};
    bool lanBroadcast{true};
    bool directIpEnabled{true};
    std::uint16_t maxPlayers{2};
    float snapThresholdMeters{2.5F};
    float interpAlpha{0.25F};
    float maxClientKbps{50.0F};
    std::string logLevel{"info"};
    std::string hostAddress{"127.0.0.1"};
};

Config loadConfig(const std::string& path);
void writeDefaultConfig(const std::string& path);

} // namespace dmp
