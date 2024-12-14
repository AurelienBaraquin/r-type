#pragma once

#include "ISystem.hpp"
#include "Loader.hpp"

class Network : public ISystem, public ILoader {
public:
    Network();

    void load(const nlohmann::json& data) override;
    std::string getPart() override;

    void update(float deltaTime, Registry& registry, ScriptSystem& scriptSystem) override;

    void initialize();
};