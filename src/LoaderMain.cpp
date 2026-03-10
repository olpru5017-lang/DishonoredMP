#include "dmp/Config.hpp"
#include "dmp/Logger.hpp"

#include <iostream>

int main(int argc, char** argv) {
    const auto configPath = (argc > 1) ? argv[1] : "dishonored_mp.cfg";
    const auto cfg = dmp::loadConfig(configPath);

    dmp::Logger::instance().setLogFile("dishonored_mp_loader.log");
    dmp::Logger::instance().info("Loader started. Target host=" + cfg.hostAddress + ":" + std::to_string(cfg.port));

    std::cout << "DishonoredMP Loader\n";
    std::cout << "1) Host Game (LAN/Direct IP)\n";
    std::cout << "2) Join Game (LAN/Direct IP)\n";
    std::cout << "3) Ready Toggle\n";
    std::cout << "Configured tick rate: " << cfg.tickRate << "Hz\n";
    std::cout << "(Injection bootstrap is expected to be implemented per launcher environment.)\n";
    return 0;
}
