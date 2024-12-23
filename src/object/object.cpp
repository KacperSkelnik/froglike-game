//
// Created by Kacper Skelnik on 09.12.2024.
//

#include "object.h"

#include "../force/force.h"

bool Object::isGrounded() const {
    return position.y + height >= screenHeight;
}

void Object::keepGrounded() {
    if (isGrounded()) {
        velocity.y = 0;
        position.y = screenHeight - height;
    }
}

void Object::pushAwayFromTheRoof() {
    if (const float center = position.y - height; center <= 0) {
        auto [x, y] = Basic(center, 270).vector();
        resultantForce.x += x;
        resultantForce.y += y;
    }
}

void Object::pushAwayFromTheLeftWall() {
    if (const float center = position.x; center <= 0) {
        auto [x, y] = Basic(-center, 0).vector();
        resultantForce.x += x;
        resultantForce.y += y;
    }
}

void Object::pushAwayFromTheRightWall() {
    if (const float center = position.x + width; center >= screenWidth) {
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
    const float      width,
    const float      height,
    const float      mass,
    const float      screenWidth,
    const float      screenHeight
):
    type(type),
    height(height),
    width(width),
    mass(mass),
    screenWidth(screenWidth),
    screenHeight(screenHeight),
    animation(animation) {}

void Object::draw() {
    applyForces();
    animation->animate(getSprite(), &position);
    restartForces();
}
