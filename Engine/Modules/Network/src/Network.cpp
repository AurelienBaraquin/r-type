#include "Network.hpp"

Network::Network()
{
    // #ifdef CLIENT
    // tryClient();
    // #elif SERVER
    // tryServer();
    // #else
    // std::cerr << "Please define either CLIENT or SERVER\n";
    // #endif
}
void Network::update(float deltaTime, Registry &registry, ScriptSystem &scriptSystem)
{
    // Update network system
}

void Network::registerComponentFactory(ComponentFactory &componentFactory)
{
    // Register network-related components
}

void Network::registerScriptBindings(ScriptSystem &scriptSystem, Registry &registry)
{
    // Register network-related script bindings
}
