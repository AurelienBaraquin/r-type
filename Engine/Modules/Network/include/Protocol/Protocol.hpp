#pragma once

#include "MessageType.hpp"
#include "Packet.hpp"

std::string serializeToString(const SnapShot& snapshot);
SnapShot deserializeFromString(const std::string& data);

Packet generatePlayerInput(int id, std::vector<std::string> dataStr);
PlayerInput loadInputFromPacket(const Packet& p);

Packet generateSnapshot(std::vector<entityData> entities);
std::vector<entityData> loadSnapshotFromPacket(const Packet& p);