//
// Created by Kacper Skelnik on 09.12.2024.
//

#include "enemy.h"

#include "../force/force.h"
#include <iostream>
#include <numbers>

Enemy::Enemy(
    Animation*       animation,
    const ObjectType type,
    const float      screenWidth,
    const float      screenHeight,
    Vector2*         heroPosition
):
    Object(
        animation,
        type,
        50,
        1,
        screenWidth,
        screenHeight
    ),
    stepForce(1),
    jumpForce(-30),
    heroPosition(heroPosition) {

    const auto initialX = static_cast<float>(GetRandomValue(static_cast<int>(radius), static_cast<int>(screenWidth - radius)));
    const float initialY = screenHeight - radius;
    this->position       = Vector2(initialX, initialY);
}

void Enemy::move() {
    frameCount++;
    if (!isGrounded() || frameCount % 100 == 0) {
        Vector2 force = {0, 0};
        if (isGrounded() && framesToLand == 0 && framesToTurn == 0) {
            const float dx    = position.x - heroPosition->x;
            const float dy    = position.y - heroPosition->y;
            const float angle = 180 - static_cast<float>(atan2(dy, dx) * 180.0f / std::numbers::pi);
            if (90 < angle && angle <= 270) {
                force = Basic(jumpForce, 45).vector();
            } else if ((270 <= angle && angle <= 360) || (0 < angle && angle <= 90)) {
                force = Basic(jumpForce, 135).vector();
            }
        } else {
            if (velocity.x < 0) {
                force = Basic(stepForce, 180).vector();
            } else {
                force = Basic(stepForce, 0).vector();
            }
        }
        resultantForce.x += force.x;
        resultantForce.y += force.y;
    }
}

SpriteDef Enemy::getSprite() {
    if (isGrounded()) {
        if (framesToLand > 0) {
            framesToLand--;
            return SpriteDef {type, LAND, side};
        }
        if (framesToTurn > 0) {
            framesToTurn--;
            return SpriteDef {type, TURN, NONE};
        }

        const float dx = position.x - heroPosition->x;
        if (dx <= 0) side = RIGHT;
        else side = LEFT;
        if (previousSide != side) {
            previousSide = side;
            framesToTurn = initialFramesToTurn;
            return SpriteDef {type, TURN, NONE};
        }
        return SpriteDef {type, IDLE, side};
    }
    if (velocity.y <= 0) {
        framesToLand = initialFramesToLand;
        return SpriteDef {type, JUMP, side};
    }
    return SpriteDef {type, FALL, side};
}