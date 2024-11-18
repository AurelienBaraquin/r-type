//
// Created by Guillaume Tran on 18/11/2024.
//

#pragma once

#include <functional>
#include "Entity.hpp"

struct BoxCollider
{
    // Used to define the hitbox position relative to the entity position
    float x, y;
    float width, height;

    // Callback called when a collision is detected
    // why not a vector of function ?
    // because collisions loop will call this function for each collision
    std::function<void(Entity const& other)> onCollisionEnter;
};