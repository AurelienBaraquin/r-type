#include "UdpServer.hpp"

#include <iostream>

UdpServer::UdpServer(asio::io_context& ioContext, unsigned short port)
    : io_(ioContext), socket_(ioContext, asio::ip::udp::endpoint(asio::ip::udp::v4(), port))
{
}

void UdpServer::start()
{
    doReceive();
}

void UdpServer::doReceive()
{
    socket_.async_receive_from(asio::buffer(recvBuffer_), remoteEndpoint_,
                               [this](std::error_code ec, std::size_t bytes_received) {
                                   if (!ec && bytes_received > 0) {
                                       handlePacket(recvBuffer_.data(), bytes_received,
                                                    remoteEndpoint_);
                                   }
                                   doReceive();  // continue receiving next packets
                               });
}

struct PlayerInput {
    uint32_t playerID;
    std::vector<std::string> actions;
};

void UdpServer::handlePacket(const uint8_t* data, size_t length,
                             const asio::ip::udp::endpoint& sender)
{
    Packet p;
    if (!p.deserialize(data, length)) {
        std::cerr << "Server: Received malformed packet from " << sender << "\n";
        return;
    }
    switch (p.getMessageType()) {
        case MessageType::PLAYER_UPDATE:
            std::cout << "Server: Player update received, seq: " << p.header.sequence << "\n";
            break;
        case MessageType::PLAYER_INPUT: {
            const uint8_t* ptr = p.payload.data();
            const uint8_t* end = ptr + p.payload.size();
            PlayerInput pi;
            if (ptr + sizeof(pi.playerID) > end) {
                std::cerr << "Server: Payload too short for playerID\n";
                return;
            }
            std::memcpy(&pi.playerID, ptr, sizeof(pi.playerID));
            ptr += sizeof(pi.playerID);
            size_t actionsCount;
            if (ptr + sizeof(actionsCount) > end) {
                std::cerr << "Server: Payload too short for actionsCount\n";
                return;
            }
            std::memcpy(&actionsCount, ptr, sizeof(actionsCount));
            ptr += sizeof(actionsCount);
            pi.actions.reserve(actionsCount);
            for (size_t i = 0; i < actionsCount; ++i) {
                size_t actionSize;
                if (ptr + sizeof(actionSize) > end) {
                    std::cerr << "Server: Payload too short for actionSize\n";
                    return;
                }
                std::memcpy(&actionSize, ptr, sizeof(actionSize));
                ptr += sizeof(actionSize);
                if (ptr + actionSize > end) {
                    std::cerr << "Server: Payload too short for action data\n";
                    return;
                }
                std::string action(reinterpret_cast<const char*>(ptr), actionSize);
                ptr += actionSize;
                pi.actions.push_back(std::move(action));
            }
            std::cout << "Server: Received PLAYER_INPUT from player " << pi.playerID << " with "
                      << pi.actions.size() << " actions.\n";
            for (const auto& act : pi.actions) {
                std::cout << "  Action: " << act << "\n";
            }
            break;
        }
        case MessageType::WORLD_EVENT:
            break;
        default:
            std::cout << "Server: Unknown message type received\n";
            break;
    }
}
