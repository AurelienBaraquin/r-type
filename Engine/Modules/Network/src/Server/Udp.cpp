#include <algorithm>
#include <iostream>

#include "Sharable.hpp"
#include "UdpServer.hpp"

UdpServer::UdpServer(asio::io_context& ioContext, unsigned short port)
    : io_(ioContext), socket_(ioContext, asio::ip::udp::endpoint(asio::ip::udp::v4(), port))
{
}

UdpServer::~UdpServer()
{
    socket_.shutdown(asio::ip::udp::socket::shutdown_both);
    socket_.close();
}

void UdpServer::start()
{
    doReceive();
}

void UdpServer::doReceive()
{
    socket_.async_receive_from(
        asio::buffer(recvBuffer_), remoteEndpoint_,
        [this](std::error_code ec, std::size_t bytes_received) {
            if (!ec && bytes_received > 0) {
                handlePacket(recvBuffer_.data(), bytes_received, remoteEndpoint_);
            } else if (ec) {
                std::cerr << "Server: Receive error: " << ec.message() << std::endl;
            }
            doReceive();
        });
}

void UdpServer::sendAll(const Packet& packet)
{
    auto data = std::make_shared<std::vector<uint8_t>>(packet.serialize());

    for (const auto& client : clients_) {
        socket_.async_send_to(asio::buffer(*data), client,
                              [data, client](std::error_code ec, std::size_t bytes_transferred) {
                                  if (ec) {
                                      std::cerr << "Server: Error sending to " << client << ": "
                                                << ec.message() << std::endl;
                                  } else {
                                  }
                              });
    }
}

void UdpServer::handlePacket(const uint8_t* data, size_t length,
                             const asio::ip::udp::endpoint& sender)
{
    auto it = std::find_if(clients_.begin(), clients_.end(),
                           [&](const auto& ep) { return ep == sender; });
    if (it == clients_.end()) {
        std::cout << "Server: New client connected from " << sender << std::endl;
        clients_.push_back(sender);
    }

    Packet p;
    if (!p.deserialize(data, length)) {
        std::cerr << "Server: Received malformed packet from " << sender << std::endl;
        return;
    }

    switch (p.getMessageType()) {
        case MessageType::PLAYER_UPDATE:
            std::cout << "Server: Player update received" << std::endl;
            break;

        case MessageType::PLAYER_INPUT: {
            PlayerInput pi = loadInputFromPacket(p);

            if (pi.actions.empty()) {
                break;
            }

            std::cout << "Server: Received PLAYER_INPUT from player " << pi.playerID << " with "
                      << pi.actions.size() << " actions.\n";
            for (const auto& act : pi.actions) {
                std::cout << "  Action: " << act << std::endl;
            }
            Sharable::getInstance().setSharedVariable("InputLoads", pi.actions);
            break;
        }

        case MessageType::WORLD_EVENT:
            std::cout << "Server: WORLD_EVENT received.\n";
            break;

        default:
            std::cout << "Server: Unknown message type received.\n";
            break;
    }
}
