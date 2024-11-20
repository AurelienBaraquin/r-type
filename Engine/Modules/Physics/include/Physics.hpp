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
    Physics() = default;
    ~Physics() override = default;
    void startup() override;
    void update(float deltaTime, Registry& registry, ScriptSystem& scriptSystem) override;
    void shutdown() override;
    void callCollideFunction(Registry& registry,Entity entity, Entity entity2, ScriptSystem& _scriptSystem);
    void registerComponentFactory(ComponentFactory& componentFactory) override;
private:
    cpSpace *_space;
    static cpBool BeginCollision(cpArbiter *arb, cpSpace *space, void *data);
    static cpBool EndCollision(cpArbiter *arb, cpSpace *space, void *data);
};