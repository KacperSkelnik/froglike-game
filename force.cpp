//
// Created by Kacper Skelnik on 05.12.2024.
//
#include "force.h"
#include <iostream>
#include <numbers>

Gravity::Gravity(const float mass): mass(mass) {
}

Vector2 Gravity::vector() {
    return Vector2(0, mass * 0.98f);
}

Basic::Basic(const float newtons, const float angle): newtons(newtons), angle(angle) {
}

Vector2 Basic::vector() {
    const auto normalizedAngle = static_cast<float>(angle * std::numbers::pi / 180.0f);
    return Vector2(newtons * cos(normalizedAngle), newtons * sin(normalizedAngle));
}

AirResistance::AirResistance(const Vector2 resultantForce, const float factor): resultantForce(resultantForce), factor(factor) {
}

Vector2 AirResistance::vector() {
    if (resultantForce.x != 0)
        return Vector2(-factor * resultantForce.x, 0);
    if (resultantForce.y != 0)
        return Vector2(0, -factor * resultantForce.y);
    return Vector2(0, 0);
}
