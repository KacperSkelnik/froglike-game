//
// Created by Kacper Skelnik on 09.12.2024.
//

#include "object.h"

#include "../force/force.h"

void Object::applyResistance() {
    auto [xResistance, _] = Resistance(velocity, 0.4).vector();
    velocity.x += xResistance;
}

void Object::applyGravity() {
    if (!isGrounded) resultantForce.y = gravity.y;
}

Object::Object(
    const ObjectType type,
    const float      mass
):
    type(type),
    mass(mass) {}
