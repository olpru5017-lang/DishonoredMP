#pragma once

#include <cstdint>
#include <optional>
#include <string>
#include <vector>

namespace dmp {

enum class AuthorityMode {
    HostAuthoritativeP2P
};

enum class AlertState {
    Relaxed,
    Suspicious,
    Alerted,
    Combat
};

enum class AbilityType {
    Blink,
    DarkVision,
    Possession,
    BendTime,
    DevouringSwarm,
    Windblast
};

struct Vec3 {
    float x{};
    float y{};
    float z{};
};

struct Quaternion {
    float x{};
    float y{};
    float z{};
    float w{1.0F};
};

struct Transform {
    Vec3 position{};
    Quaternion rotation{};
    Vec3 velocity{};
};

struct AnimationState {
    std::string locomotion;
    bool crouched{};
    bool sprinting{};
    bool leaning{};
    bool jumping{};
    bool combatStance{};
    bool takedown{};
    bool swordAttack{};
    bool blinkActive{};
    bool possessionExit{};
};

struct PlayerState {
    std::uint32_t netId{};
    std::string nickname;
    Transform transform;
    Vec3 aimDirection{};
    float health{100.0F};
    float mana{100.0F};
    std::string equippedWeapon{"Sword"};
    std::vector<std::string> inventory;
    AnimationState animation;
};

struct AIState {
    std::uint32_t actorId{};
    AlertState alert{AlertState::Relaxed};
    float suspicion{};
    std::optional<std::uint32_t> targetNetId;
    std::string behavior;
};

struct Snapshot {
    std::uint64_t tick{};
    std::vector<PlayerState> players;
    std::vector<AIState> aiActors;
};

} // namespace dmp
