#include <iostream>

#include "UdpClient.hpp"

UdpClient::UdpClient(asio::io_context& ioContext, const asio::ip::udp::endpoint& serverEndpoint)
    : io_(ioContext),
      socket_(ioContext, asio::ip::udp::endpoint(asio::ip::udp::v4(), 0)),
      serverEndpoint_(serverEndpoint)
{
}

void UdpClient::sendPacket(const Packet& packet)
{
    auto buffer = packet.serialize();
    size_t sent = socket_.send_to(asio::buffer(buffer), serverEndpoint_);
}

void UdpClient::startReceiving()
{
    doReceive();
}

void UdpClient::doReceive()
{
    std::cout << "Client: Waiting for data...\n";
    socket_.async_receive_from(asio::buffer(recvBuffer_), remoteEndpoint_,
                               [this](std::error_code ec, std::size_t bytes_received) {
                                   handleReceive(ec, bytes_received);
                               });
}

void UdpClient::handleReceive(const std::error_code& ec, std::size_t bytes_received)
{
    if (!ec && bytes_received > 0) {
        Packet p;
        if (p.deserialize(recvBuffer_.data(), bytes_received)) {
            switch (p.getMessageType()) {
                case MessageType::PLAYER_UPDATE:
                    std::cout << "Client: Received PLAYER_UPDATE from server.\n";
                    break;
                case MessageType::WORLD_EVENT:
                    std::cout << "Client: Received WORLD_EVENT from server.\n";
                    break;
                case MessageType::PLAYER_INPUT: {
                    PlayerInput pi = loadInputFromPacket(p);

                    if (pi.actions.empty()) {
                        break;
                    }
                    std::cout << "Client: Received PLAYER_INPUT from server.\n";
                    break;
                }
                default:
                    std::cout << "Client: Received unknown message type.\n";
                    break;
            }
        } else {
            std::cerr << "Client: Received malformed packet.\n";
        }
    }
    doReceive();
}
