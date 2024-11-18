#pragma once

struct Position {
    float x, y, z;

    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) {
        ar & x & y & z;
    }
};
