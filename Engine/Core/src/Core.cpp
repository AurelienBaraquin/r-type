#include "Core.hpp"
#include <iostream>
#include "Registry.hpp"

Core::Core()
{
}

Core::~Core()
{
}

struct Position {
    float x, y, z;

    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) {
        ar & x & y & z;
    }
};

struct Velocity {
    float dx, dy;

    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) {
        ar & dx & dy;
    }
};

void Core::run() {
    auto entity1 = _registry.createEntity();
    auto entity2 = _registry.createEntity();

    _registry.addComponent<Position>(entity1, 10.0f, 20.0f, 30.0f);
    _registry.addComponent<Velocity>(entity1, 1.0f, 1.5f);
    _registry.addComponent<Position>(entity2, 30.0f, 40.0f, 50.0f);
    _registry.addComponent<Velocity>(entity2, 2.0f, 2.5f);

    auto entities = _registry.view<Position, Velocity>();
    for (auto entity : entities) {
        auto pos = _registry.getComponent<Position>(entity);
        auto vel = _registry.getComponent<Velocity>(entity);
        std::cout << "Entity " << entity << ": Position (" << pos->x << ", " << pos->y << ", " << pos->z << "), Velocity (" << vel->dx << ", " << vel->dy << ")" << std::endl;
    }
}
