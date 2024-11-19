//
// Created by Guillaume Tran on 19/11/2024.
//

#pragma once

#include "ISystem.hpp"
#include "Registry.hpp"
#include "BoxCollider.hpp"

class Physics : public ISystem
{
    public:
    Physics() = default;
    ~Physics() override = default;
    void startup() override;
    void update(float deltaTime, Registry& registry) override;
    void shutdown() override;
};
