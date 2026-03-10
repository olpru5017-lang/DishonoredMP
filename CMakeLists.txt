cmake_minimum_required(VERSION 3.20)
project(DishonoredMP VERSION 0.2.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

option(DMP_BUILD_TESTS "Build tests" ON)

add_library(dmp_core STATIC
    src/Config.cpp
    src/Logger.cpp
    src/NetworkTypes.cpp
    src/Replication.cpp
    src/AbilitySystem.cpp
    src/AISync.cpp
    src/InterestManagement.cpp
    src/TimeBubble.cpp
    src/ProxyAvatar.cpp
    src/Plugin.cpp
    src/Hooking.cpp
    src/MenuIntegration.cpp
)

target_include_directories(dmp_core PUBLIC include)
target_compile_definitions(dmp_core PRIVATE NOMINMAX)

add_library(dishonored_mp SHARED src/DllMain.cpp)
target_link_libraries(dishonored_mp PRIVATE dmp_core)
set_target_properties(dishonored_mp PROPERTIES OUTPUT_NAME "dishonored_mp")

if (DMP_BUILD_TESTS)
  enable_testing()
  add_executable(dmp_smoke_test tests/SmokeTest.cpp)
  target_link_libraries(dmp_smoke_test PRIVATE dmp_core)
  add_test(NAME dmp_smoke COMMAND dmp_smoke_test)
endif()
