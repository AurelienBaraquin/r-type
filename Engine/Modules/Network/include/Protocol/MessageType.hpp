#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "Transform.hpp"

enum class MessageType : uint8_t {
    PLAYER_UPDATE = 1,
    WORLD_EVENT = 2,
    SNAPSHOT = 3,
    PLAYER_INPUT = 4,
};

struct PlayerInput {
    int playerID;
    std::vector<std::string> actions;
};

struct entityData {
    int entityID;
    Components::Position pos;
};

struct SnapShot {
    size_t id;
    std::vector<entityData> entities;
};
