#pragma once

struct Velocity {
    float dx, dy;

    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) {
        ar & dx & dy;
    }
};
