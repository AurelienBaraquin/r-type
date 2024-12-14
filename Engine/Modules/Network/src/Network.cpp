#include "Network.hpp"
#include "Registry.hpp"
#include "ScriptSystem.hpp"

Network::Network() {
    // constructor implementation
}

void Network::load(const nlohmann::json& data) {
    // load implementation
}

std::string Network::getPart() {
    return "NetworkPart";
}

void Network::initialize() {
    // initialize implementation
}

#ifdef CLIENT

void Network::update(float deltaTime, Registry& registry, ScriptSystem& scriptSystem) {
    std::cout << "Updating the client network system..." << std::endl;
    // Provide the logic for updating the network system.
    // This can be anything you need: handling network events, sending/receiving data, etc.
}
#endif

#ifdef SERVER
void Network::update(float deltaTime, Registry& registry, ScriptSystem& scriptSystem) {
    std::cout << "Updating the server network system..." << std::endl;
    // Provide the logic for updating the network system.
    // This can be anything you need: handling network events, sending/receiving data, etc.
}
#endif