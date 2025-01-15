#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "Transform.hpp"
#include "Entity.hpp"
#include <cereal/cereal.hpp>
#include <cereal/archives/binary.hpp>
#include <cereal/types/vector.hpp>
#include <sstream>

enum class MessageType : uint8_t {
    PLAYER_UPDATE = 1,
    WORLD_EVENT = 2,
    SNAPSHOT = 3,
    PLAYER_INPUT = 4,
};

struct PlayerInput {
    int playerID;
    std::vector<std::string> actions;

    template<class Archive> 
    void serialize(Archive & ar) 
    { 
        ar(playerID, actions); 
    } 
};

struct entityData {
    Entity entity;
    int x, y, z;

    template<class Archive> 
    void serialize(Archive & ar) 
    { 
        ar(entity, x, y, z); 
    } 
};

struct SnapShot {
    size_t id;
    std::vector<entityData> entities;

    template<class Archive>
    void serialize(Archive & archive) {
        archive(id, entities);
    }
};
