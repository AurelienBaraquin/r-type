project(Network)

add_library(Network STATIC 
    src/Network.cpp
    src/Client.cpp
    src/Protocol.cpp
    src/Server.cpp
    src/UdpClient.cpp
    src/UdpServer.cpp
)

target_include_directories(Network PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/components
)

target_link_libraries(Network PRIVATE Core nlohmann_json::nlohmann_json)
target_link_libraries(Network PRIVATE Core asio::asio)

add_library(Engine::Network ALIAS Network)