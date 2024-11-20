//
// Created by Guillaume Tran on 19/11/2024.
//

#pragma once
#include <chipmunk/chipmunk.h>
#include "BoxCollider.hpp"
#include "ISystem.hpp"
#include "Registry.hpp"
#include <memory>
#include <SDL2/SDL.h>
#include "Core.hpp"

class Physics : public ISystem
{
   public:
    Physics(ScriptSystem& ScriptSystem);
    ~Physics() override = default;
    void startup() override;
    void update(float deltaTime, Registry& registry) override;
    void shutdown() override;

    void registerComponentFactory(ComponentFactory& componentFactory) override;
private:
    ScriptSystem& _scriptSystem;
    cpSpace *_space;
    static cpBool BeginCollision(cpArbiter *arb, cpSpace *space, void *data);
    static cpBool EndCollision(cpArbiter *arb, cpSpace *space, void *data);
};