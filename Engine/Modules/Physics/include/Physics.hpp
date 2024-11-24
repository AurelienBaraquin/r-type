//
// Created by Guillaume Tran on 19/11/2024.
//

#pragma once
#include <chipmunk/chipmunk.h>

#include <memory>

#include "BoxCollider.hpp"
#include "Core.hpp"
#include "ISystem.hpp"
#include "Registry.hpp"

class Physics : public ISystem
{
   public:
    Physics() = default;
    ~Physics() override;
    void update(float deltaTime, Registry &registry, ScriptSystem &scriptSystem) override;
    void callFunction(Registry &registry,
                      Entity entity, Entity entity2,
                        std::string function, ScriptSystem &_scriptSystem);
    void registerComponentFactory(ComponentFactory &componentFactory) override;
    void updateCollision(Registry &registry, Entity entity, Entity entity2,
                         ScriptSystem &_scriptSystem);
   private:
    cpSpace *_space;
    static cpBool BeginCollision(cpArbiter *arb, cpSpace *space, void *data);
    static cpBool EndCollision(cpArbiter *arb, cpSpace *space, void *data);
};