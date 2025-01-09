#pragma once

#include <asio.hpp>
#include <iostream>

#include "ISystem.hpp"
#include "Loader.hpp"
#include "Protocol.hpp"
#include "UdpClient.hpp"
#include "UdpServer.hpp"

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

   private:
    asio::io_context ioContext;
#ifdef SERVER
    UdpServer server;
#elif CLIENT
    UdpClient client;
#endif
};
