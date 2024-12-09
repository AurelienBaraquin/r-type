#pragma once

#include "ISystem.hpp"
#include "Loader.hpp"
#include <asio.hpp>

class Network : public ISystem, public ILoader
{
   public:
    Network();

    ~Network() override;

    void update(float deltaTime, Registry& registry, ScriptSystem& scriptSystem) override;
    void registerScriptBindings(ScriptSystem& ScriptSystem, Registry& registry) override;
    void registerComponentFactory(ComponentFactory& componentFactory) override;

   private:
    // Add any necessary private members here
};
