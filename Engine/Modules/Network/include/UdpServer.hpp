#pragma once

#include <asio.hpp>
#include <functional>
#include <memory>
#include <thread>
#include <unordered_set>
#include <vector>

#include "Protocol.hpp"

class UdpServer
{
   public:
    UdpServer(asio::io_context& ioContext, unsigned short port);
    ~UdpServer();
    void start();

    int countClients() const
    {
        return static_cast<int>(clients_.size());
    }

    void sendAll(const Packet& packet);

   private:
    void doReceive();
    void handlePacket(const uint8_t* data, size_t length, const asio::ip::udp::endpoint& sender);

    asio::io_context& io_;
    asio::ip::udp::socket socket_;
    asio::ip::udp::endpoint remoteEndpoint_;
    std::array<uint8_t, 2048> recvBuffer_;
    std::vector<asio::ip::udp::endpoint> clients_;
};
