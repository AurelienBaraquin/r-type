#pragma once

#include <cstdint>
#include <limits>
#include <string>

using Entity = uint32_t;
constexpr Entity INVALID_ENTITY = std::numeric_limits<Entity>::max();

using Tag = std::string;
