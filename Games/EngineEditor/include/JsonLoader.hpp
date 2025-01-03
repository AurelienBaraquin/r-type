//
// Created by Guillaume Tran on 03/01/2025.
//

#pragma once

#include "Scene.hpp"
#include <nlohmann/json.hpp>

class JsonLoader {
public:
    static Scene loadScene(const std::string &filename);
};
