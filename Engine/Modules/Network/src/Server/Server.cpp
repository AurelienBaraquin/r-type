#include <asio.hpp>
#include <iostream>

#include "Network.hpp"
#include "Sharable.hpp"
#include "UdpServer.hpp"

#ifdef SERVER
Network::Network() : ioContext(), server(ioContext, 12345)
{
    try {
        server.start();

        std::thread t([this]() { this->ioContext.run(); });

        std::cout << "Server running on port 12345...\n";

        t.detach();

    } catch (std::exception &e) {
        std::cerr << "Server exception: " << e.what() << "\n";
    }
}

void Network::update(float deltaTime, Registry &registry, ScriptSystem &scriptSystem)
{
    // std::cout << server.countClients() << std::endl;
}
#endif