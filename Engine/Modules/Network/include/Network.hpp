#pragma once

#include "ISystem.hpp"
#include "Loader.hpp"

class Network : public ISystem, public ILoader
{
   public:
    Network();
    ~Network() = default;
    void update(float deltaTime, Registry &registry, ScriptSystem &scriptSystem) override;
    void registerComponentFactory(ComponentFactory &componentFactory) override;
    void registerScriptBindings(ScriptSystem &scriptSystem, Registry &registry) override;

    void load(const nlohmann::json &data) override {};
    std::string getPart() override
    {
        return "network";
    }
};

int tryClient();
int tryServer();
