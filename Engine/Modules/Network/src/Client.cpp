#include <asio.hpp>
#include <iostream>

#include "Network.hpp"
#include "UdpClient.hpp"

void tryClient()
{
    try {
        asio::io_context ioContext;
        asio::ip::udp::endpoint serverEndpoint(asio::ip::address::from_string("127.0.0.1"), 12345);
        UdpClient client(ioContext, serverEndpoint);

        Packet p;
        p.setMessageType(MessageType::PLAYER_UPDATE);
        p.setSequence(1);

        struct PlayerUpdate {
            uint32_t playerID;
            float pos[3];
            float vel[3];
        } pu;
        pu.playerID = 42;
        pu.pos[0] = 1.0f;
        pu.pos[1] = 2.0f;
        pu.pos[2] = 3.0f;
        pu.vel[0] = 0.0f;
        pu.vel[1] = 0.0f;
        pu.vel[2] = 0.0f;

        std::vector<uint8_t> payload(sizeof(PlayerUpdate));
        std::memcpy(payload.data(), &pu, sizeof(PlayerUpdate));
        p.setPayload(payload);

        client.sendPacket(p);
        // std::cout << "Client: Packet sent.\n";
    } catch (std::exception& e) {
        std::cerr << "Client exception: " << e.what() << "\n";
    }
}
