//
// Created by Guillaume Tran on 18/11/2024.
//

#pragma once
#include "raylib.h"
#include <functional>

struct BoxCollider {
    Rectangle rect;
    std::function<void()> onBoxColliderEntered;
    std::function<void()> onBoxColliderExited;
};