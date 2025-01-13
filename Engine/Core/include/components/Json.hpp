#pragma once

#include <string>
#include <nlohmann/json.hpp>

namespace Components {
struct Json {
    nlohmann::json data;
};
} 