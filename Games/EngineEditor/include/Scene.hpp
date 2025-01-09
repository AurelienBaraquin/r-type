    //
// Created by Guillaume Tran on 03/01/2025.
//

#pragma once
#include "Entity.hpp"

class Scene {
public:
    Scene() = default;
    ~Scene() = default;
private:
    std::vector<Entity> entities;
};
