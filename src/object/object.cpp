//
// Created by Kacper Skelnik on 09.12.2024.
//

#include "object.h"

#include "../force/force.h"

bool Object::isGrounded() const {
    return position.y + radius + 0.05 * radius >= screenHeight;
}

void Object::keepGrounded() {
    if (isGrounded()) {
        velocity.y = 0;
        position.y = screenHeight - radius;
    }
}

void Object::pushAwayFromTheRoof() {
    if (const float center = position.y - radius; center <= 0) {
        auto [x, y] = Basic(center, 270).vector();
        resultantForce.x += x;
        resultantForce.y += y;
    }
}

void Object::pushAwayFromTheLeftWall() {
    if (const float center = position.x - radius; center <= 0) {
        auto [x, y] = Basic(-center, 0).vector();
        resultantForce.x += x;
        resultantForce.y += y;
    }
}

void Object::pushAwayFromTheRightWall() {
    if (const float center = position.x + radius; center >= screenWidth) {
        auto [x, y] = Basic(center - screenWidth, 180).vector();
        resultantForce.x += x;
        resultantForce.y += y;
    }
}

void Object::applyAirResistance() {
    auto [xResistance, yResistance] = AirResistance(velocity, 0.1).vector();
    resultantForce.x += xResistance;
    resultantForce.y += yResistance;
}

void Object::applyForces() {
    pushAwayFromTheRoof();
    pushAwayFromTheLeftWall();
    pushAwayFromTheRightWall();
    applyAirResistance();

    velocity.x += resultantForce.x / mass;
    velocity.y += resultantForce.y / mass;
    position.x += velocity.x;
    position.y += velocity.y;

    keepGrounded();
}

void Object::restartForces() {
    resultantForce = gravity;
}

Object::Object(
    Animation*       animation,
    const ObjectType type,
    const float      radius,
    const float      mass,
    const float      screenWidth,
    const float      screenHeight
):
    type(type),
    radius(radius),
    mass(mass),
    screenWidth(screenWidth),
    screenHeight(screenHeight),
    animation(animation) {}

void Object::draw() {
    applyForces();
    animation->animate(getSprite(), &position);
    restartForces();
}
