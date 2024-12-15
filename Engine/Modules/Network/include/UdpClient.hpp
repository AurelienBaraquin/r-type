#pragma once

#include <asio.hpp>
#include <functional>
#include <thread>

#include "Protocol.hpp"

class UdpClient
{
   public:
    UdpClient(asio::io_context& ioContext, const asio::ip::udp::endpoint& serverEndpoint);
    void sendPacket(const Packet& packet);

   private:
    asio::io_context& io_;
    asio::ip::udp::socket socket_;
    asio::ip::udp::endpoint serverEndpoint_;
};
