#include <asio.hpp>
#include <chrono>
#include <iostream>

#include "Network.hpp"
#include "Sharable.hpp"
#include "Transform.hpp"
#include "UdpServer.hpp"

#ifdef SERVER
Network::Network() : ioContext(), server(ioContext, 12345)
{
    try {
        server.start();

        std::thread t([this]() { this->ioContext.run(); });

        // std::cout << "Server running on port 12345...\n";

        t.detach();

    } catch (std::exception &e) {
        std::cerr << "Server exception: " << e.what() << std::endl;
    }
}

Packet Network::snapShot(Registry &registry)
{
    std::ostringstream os;
    {
        if (!os) {
            std::cerr << "Failed to open string stream for saving.\n";
            return Packet();
        }
        cereal::BinaryOutputArchive archive(os);
        registry.save(archive);
        std::cout << "Registry saved successfully.\n";
    }
    std::string registryData = os.str();

    return generateSnapshot(registry);
}
void Network::update(float deltaTime, Registry &registry, ScriptSystem &scriptSystem)
{
    static auto lastSnapShotTime = std::chrono::steady_clock::now();
    auto currentTime = std::chrono::steady_clock::now();
    std::chrono::duration<float> elapsedTime = currentTime - lastSnapShotTime;

    if (elapsedTime.count() >= 0.1f) {

        Packet newPack = snapShot(registry);
        if (newPack.getMessageType() == MessageType::SNAPSHOT) {
            server.sendAll(newPack);
            lastSnapShotTime = currentTime;
        }
    }
}
#endif
