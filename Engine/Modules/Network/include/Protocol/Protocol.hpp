#pragma once

#include "MessageType.hpp"
#include "Packet.hpp"
#include "Serialization.hpp"

const std::vector<entityData>& getSnapShot();
void setSnapshot(const std::vector<entityData>& newSnapshot);
