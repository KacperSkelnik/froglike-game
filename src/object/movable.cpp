//
// Created by Kacper Skelnik on 11.01.2025.
//

#include "movable.h"

#include "../force/force.h"

void Movable::applyResistance() {
    auto [xResistance, _] = Resistance(velocity, 0.4).vector();
    velocity.x += xResistance;
}

void Movable::applyGravity() {
    if (!isGrounded) resultantForce.y = gravity.y;
}

Movable::Movable(const float mass): mass(mass) {}