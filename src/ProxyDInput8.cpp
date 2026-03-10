#include "dmp/Config.hpp"
#include "dmp/Logger.hpp"
#include "dmp/Plugin.hpp"

#include <memory>
#include <string>

namespace {
std::unique_ptr<dmp::DishonoredMPPlugin> g_plugin;

void initializePlugin() {
    const auto cfg = dmp::loadConfig("dishonored_mp.cfg");
    dmp::Logger::instance().setLogFile("dishonored_mp.log");
    g_plugin = std::make_unique<dmp::DishonoredMPPlugin>(cfg);
    g_plugin->onMainMenuFrame();
    dmp::Logger::instance().info("DishonoredMP loaded via dinput8 proxy. Multiplayer button hook initialized.");
}
}

#if defined(_WIN32)
#include <Windows.h>

typedef HRESULT(WINAPI* DirectInput8CreateFn)(HINSTANCE, DWORD, REFIID, LPVOID*, LPUNKNOWN);

static HMODULE g_realDInput8 = nullptr;
static DirectInput8CreateFn g_realDirectInput8Create = nullptr;

static void loadSystemDInput8() {
    if (g_realDInput8) {
        return;
    }

    char systemPath[MAX_PATH] = {};
    GetSystemDirectoryA(systemPath, MAX_PATH);
    const std::string dllPath = std::string(systemPath) + "\\dinput8.dll";

    g_realDInput8 = LoadLibraryA(dllPath.c_str());
    if (g_realDInput8) {
        g_realDirectInput8Create = reinterpret_cast<DirectInput8CreateFn>(GetProcAddress(g_realDInput8, "DirectInput8Create"));
    }
}

extern "C" __declspec(dllexport) HRESULT WINAPI DirectInput8Create(HINSTANCE hinst, DWORD dwVersion, REFIID riidltf,
                                                                      LPVOID* ppvOut, LPUNKNOWN punkOuter) {
    loadSystemDInput8();
    if (!g_realDirectInput8Create) {
        return E_FAIL;
    }
    return g_realDirectInput8Create(hinst, dwVersion, riidltf, ppvOut, punkOuter);
}

BOOL APIENTRY DllMain(HMODULE, DWORD reason, LPVOID) {
    if (reason == DLL_PROCESS_ATTACH) {
        initializePlugin();
    }
    if (reason == DLL_PROCESS_DETACH) {
        if (g_realDInput8) {
            FreeLibrary(g_realDInput8);
            g_realDInput8 = nullptr;
        }
    }
    return TRUE;
}
#else
extern "C" void dishonored_mp_init() { initializePlugin(); }
#endif
