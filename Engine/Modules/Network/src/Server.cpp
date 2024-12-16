#include <asio.hpp>
#include <iostream>

#include "Network.hpp"
#include "UdpServer.hpp"

void tryServer()
{
    try {
        asio::io_context ioContext;
        UdpServer server(ioContext, 12345);
        server.start();

        std::thread t([&ioContext]() { ioContext.run(); });

        std::cout << "Server running on port 12345...\n";

        t.join();
        
    } catch (std::exception& e) {
        std::cerr << "Server exception: " << e.what() << "\n";
    }
}
