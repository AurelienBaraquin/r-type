project(Network)

add_library(Network STATIC 
    src/Network.cpp
    src/Protocol/Protocol.cpp
    src/Protocol/Packet.cpp
    src/Client/Client.cpp
    src/Client/Udp.cpp
    src/Server/Server.cpp
    src/Server/Udp.cpp
    src/Protocol/PlayerInput.cpp
    src/Protocol/SnapShot.cpp
)

target_include_directories(Network PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/components
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Protocol
)

target_link_libraries(Network PUBLIC Core nlohmann_json::nlohmann_json asio::asio cereal::cereal)

add_library(Engine::Network ALIAS Network)
