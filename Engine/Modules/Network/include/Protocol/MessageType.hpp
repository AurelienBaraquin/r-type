#pragma once

#include <cstdint>
#include <string>
#include <vector>

enum class MessageType : uint8_t {
    PLAYER_UPDATE = 1,
    WORLD_EVENT = 2,
    SERVER_SNAPSHOT = 3,
    PLAYER_INPUT = 4,
};

struct PlayerInput {
    uint32_t playerID;
    std::vector<std::string> actions;
};
