#pragma once

#include "MessageType.hpp"
#include "Packet.hpp"
#include "Serialization.hpp"

Packet generatePlayerInput(int id, std::vector<std::string> dataStr);
PlayerInput loadInputFromPacket(const Packet& p);

Packet generateSnapshot(std::vector<entityData> entities);
std::vector<entityData> loadSnapshotFromPacket(const Packet& p);