#pragma once

#include <cereal/archives/binary.hpp>
namespace Components {
struct Position {
    int x, y, z;

    template <class Archive>
    void serialize(Archive& ar)
    {
        ar(x, y, z);
    }
};

struct Scale {
    int x, y;
    template <class Archive>
    void serialize(Archive& ar)
    {
        ar(x, y);
    }
};

struct Rotation {
    float angle;
    template <class Archive>
    void serialize(Archive& ar)
    {
        ar(angle);
    }
};
}  // namespace Components
