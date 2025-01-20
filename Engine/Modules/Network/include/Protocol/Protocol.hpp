#pragma once

#include "MessageType.hpp"
#include "Packet.hpp"
#include "Serialization.hpp"

const Packet& getSnapShot();
void setSnapshot(const Packet& newSnapshot);