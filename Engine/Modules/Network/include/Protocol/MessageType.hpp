#pragma once

#include <cereal/archives/binary.hpp>
#include <cereal/cereal.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/vector.hpp>
#include <cstdint>
#include <sstream>
#include <string>
#include <vector>

#include "Entity.hpp"
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

    template <class Archive>
    void serialize(Archive& ar)
    {
        ar(playerID, actions);
    }
};

struct entityData {
    Entity entity;
    Components::Position pos;
    Components::Scale scale;
    Components::Rotation rot;
    std::vector<Tag> tag;

    template <class Archive>
    void serialize(Archive& ar)
    {
        ar(entity, pos, scale, rot, tag);
    }
};

struct SnapShot {
    size_t id;
    std::vector<entityData> entities;

    template <class Archive>
    void serialize(Archive& archive)
    {
        archive(id, entities);
    }
};
