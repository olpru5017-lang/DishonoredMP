#include "dmp/Config.hpp"
#include "dmp/Logger.hpp"
#include "dmp/Plugin.hpp"

#include <memory>

namespace {
std::unique_ptr<dmp::DishonoredMPPlugin> g_plugin;

void initializePlugin() {
    const auto cfg = dmp::loadConfig("dishonored_mp.cfg");
    dmp::Logger::instance().setLogFile("dishonored_mp.log");
    g_plugin = std::make_unique<dmp::DishonoredMPPlugin>(cfg);
    g_plugin->onMainMenuFrame();
    dmp::Logger::instance().info("Plugin bootstrap complete. Multiplayer menu button injected.");
}
}

#if defined(_WIN32)
#include <Windows.h>

BOOL APIENTRY DllMain(HMODULE, DWORD reason, LPVOID) {
    if (reason == DLL_PROCESS_ATTACH) {
        initializePlugin();
    }
    return TRUE;
}
#else
extern "C" void dishonored_mp_init() {
    initializePlugin();
}
#endif
