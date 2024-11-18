#include <gtest/gtest.h>
#include "Serialization.hpp"

#include "Position.hpp"

TEST(SerializationTest, SerializeDeserializePosition) {
    Position pos1{10.5f, 20.75f};
    std::string serialized = serialize(pos1);
    Position pos2 = deserialize<Position>(serialized);
    EXPECT_EQ(pos1.x, pos2.x);
    EXPECT_EQ(pos1.y, pos2.y);
}

TEST(SerializationTest, SerializeEmptyPosition) {
    Position pos1{0.0f, 0.0f};
    std::string serialized = serialize(pos1);
    Position pos2 = deserialize<Position>(serialized);
    EXPECT_EQ(pos1.x, pos2.x);
    EXPECT_EQ(pos1.y, pos2.y);
}

#include "Velocity.hpp"

TEST(SerializationTest, SerializeDeserializeVelocity) {
    Velocity vel1{1.5f, 2.5f};
    std::string serialized = serialize(vel1);
    Velocity vel2 = deserialize<Velocity>(serialized);
    EXPECT_EQ(vel1.dx, vel2.dx);
    EXPECT_EQ(vel1.dy, vel2.dy);
}

TEST(SerializationTest, SerializeEmptyVelocity) {
    Velocity vel1{0.0f, 0.0f};
    std::string serialized = serialize(vel1);
    Velocity vel2 = deserialize<Velocity>(serialized);
    EXPECT_EQ(vel1.dx, vel2.dx);
    EXPECT_EQ(vel1.dy, vel2.dy);
}
