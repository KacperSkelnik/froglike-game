//
// Created by Kacper Skelnik on 05.12.2024.
//
#include "hero.h"

#include "../force/force.h"

SpriteDef Hero::getSprite() {
    return SpriteDef {type, TURN, LEFT};
}

Hero::Hero(
    Animation*       animation,
    const ObjectType type,
    const float      screenWidth,
    const float      screenHeight
):
    Object(
        animation,
        type,
        50,
        1,
        screenWidth,
        screenHeight
    ),
    stepForce(2.0f),
    jumpForce(-25.0f),
    isSquatting(false) {

    this->gravity  = Gravity(mass).vector();
    this->position = Vector2(screenWidth / 2, screenHeight - radius);
}

void Hero::move() {
    const bool grounded = isGrounded();
    // jumping
    if (IsKeyDown(KEY_UP) && grounded) {
        auto [x, y] = Basic(jumpForce, 90).vector();
        resultantForce.x += x;
        resultantForce.y += y;
    }

    // squatting
    if (IsKeyDown(KEY_DOWN) && grounded && !isSquatting) {
        radius      = radius / 2;
        position.y  = screenHeight - radius;
        isSquatting = true;
    }
    if ((!IsKeyDown(KEY_DOWN) && isSquatting) || (!grounded && isSquatting)) {
        radius      = radius * 2;
        position.y  = screenHeight - radius;
        isSquatting = false;
    }

    // left/right
    if (IsKeyDown(KEY_RIGHT)) {
        auto [x, y] = Basic(stepForce, 0).vector();
        resultantForce.x += x;
        resultantForce.y += y;
    }
    if (IsKeyDown(KEY_LEFT)) {
        auto [x, y] = Basic(stepForce, 180).vector();
        resultantForce.x += x;
        resultantForce.y += y;
    }
}

void Hero::draw() {
    applyForces();
    DrawCircleV(position, radius, MAROON);
    restartForces();
}