#include "Protocol.hpp"

// PlayerInput loadInputFromPacket(const Packet& packet)
// {
//     const uint8_t* ptr = p.payload.data();
//     const uint8_t* end = ptr + p.payload.size();
//     PlayerInput pi;

//     if (ptr + sizeof(pi.playerID) > end) {
//         std::cerr << "Server: Payload too short for playerID\n";
//         retur pi;
//     }
//     std::memcpy(&pi.playerID, ptr, sizeof(pi.playerID));
//     ptr += sizeof(pi.playerID);

//     size_t actionsCount;
//     if (ptr + sizeof(actionsCount) > end) {
//         std::cerr << "Server: Payload too short for actionsCount\n";
//         return;
//     }
//     std::memcpy(&actionsCount, ptr, sizeof(actionsCount));
//     ptr += sizeof(actionsCount);

//     pi.actions.reserve(actionsCount);
//     for (size_t i = 0; i < actionsCount; ++i) {
//         size_t actionSize;
//         if (ptr + sizeof(actionSize) > end) {
//             std::cerr << "Server: Payload too short for actionSize\n";
//             return;
//         }
//         std::memcpy(&actionSize, ptr, sizeof(actionSize));
//         ptr += sizeof(actionSize);

//         if (ptr + actionSize > end) {
//             std::cerr << "Server: Payload too short for action data\n";
//             return;
//         }
//         std::string action(reinterpret_cast<const char*>(ptr), actionSize);
//         ptr += actionSize;
//         pi.actions.push_back(std::move(action));
//     }
// }
