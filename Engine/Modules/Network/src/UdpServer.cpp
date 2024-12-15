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

void UdpServer::handlePacket(const uint8_t* data, size_t length,
                             const asio::ip::udp::endpoint& sender)
{
    Packet p;
    if (!p.deserialize(data, length)) {
        // Malformed packet
        std::cerr << "Server: Received malformed packet from " << sender << "\n";
        return;
    }

    switch (p.getMessageType()) {
        case MessageType::PLAYER_UPDATE:
            std::cout << "Server: Player update received, seq: " << p.header.sequence << "\n";
            // parse the payload and update player state
            break;
        case MessageType::WORLD_EVENT:
            // handle event
            break;
        default:
            std::cout << "Server: Unknown message type received\n";
            break;
    }
}