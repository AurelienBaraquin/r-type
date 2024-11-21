#pragma once

#include <cstdint>
#include <limits>
#include <string>

using Entity = uint32_t;

#ifdef _WIN32
#define INVALID_ENTITY UINT32_MAX
#else
constexpr Entity INVALID_ENTITY = std::numeric_limits<Entity>::max();
#endif

using Tag = std::string;
