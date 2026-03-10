#include "dmp/Config.hpp"

#include <fstream>
#include <sstream>
#include <stdexcept>

namespace dmp {

namespace {

void parseLine(const std::string& line, Config& cfg) {
    const auto pos = line.find('=');
    if (pos == std::string::npos) {
        return;
    }

    const auto key = line.substr(0, pos);
    const auto value = line.substr(pos + 1);

    if (key == "port") cfg.port = static_cast<std::uint16_t>(std::stoi(value));
    else if (key == "tickRate") cfg.tickRate = static_cast<std::uint16_t>(std::stoi(value));
    else if (key == "lanBroadcast") cfg.lanBroadcast = (value == "true");
    else if (key == "directIpEnabled") cfg.directIpEnabled = (value == "true");
    else if (key == "maxPlayers") cfg.maxPlayers = static_cast<std::uint16_t>(std::stoi(value));
    else if (key == "snapThresholdMeters") cfg.snapThresholdMeters = std::stof(value);
    else if (key == "interpAlpha") cfg.interpAlpha = std::stof(value);
    else if (key == "maxClientKbps") cfg.maxClientKbps = std::stof(value);
    else if (key == "logLevel") cfg.logLevel = value;
    else if (key == "hostAddress") cfg.hostAddress = value;
}

} // namespace

Config loadConfig(const std::string& path) {
    std::ifstream in(path);
    if (!in) {
        writeDefaultConfig(path);
        return Config{};
    }

    Config cfg;
    std::string line;
    while (std::getline(in, line)) {
        parseLine(line, cfg);
    }
    return cfg;
}

void writeDefaultConfig(const std::string& path) {
    std::ofstream out(path);
    if (!out) {
        throw std::runtime_error("Failed to write config to " + path);
    }

    out << "port=30777\n";
    out << "tickRate=60\n";
    out << "lanBroadcast=true\n";
    out << "directIpEnabled=true\n";
    out << "maxPlayers=2\n";
    out << "snapThresholdMeters=2.5\n";
    out << "interpAlpha=0.25\n";
    out << "maxClientKbps=50\n";
    out << "logLevel=info\n";
    out << "hostAddress=127.0.0.1\n";
}

} // namespace dmp
