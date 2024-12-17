//
// Created by Kacper Skelnik on 05.12.2024.
//
#include "hero.h"

#include "../force/force.h"

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
    jumpForce(-25.0f) {

    this->gravity  = Gravity(mass).vector();
    this->position = Vector2(screenWidth / 2, screenHeight - radius);
}

void Hero::move() {
    auto leftRightMovement = [](Hero* hero, bool isGrounded) -> void {
        if (IsKeyDown(KEY_RIGHT)) {
            auto [x, _] = Basic(hero->stepForce, 0).vector();
            hero->resultantForce.x += x;
            hero->side = RIGHT;
            if (isGrounded) hero->isWalking = true;
        }
        if (IsKeyDown(KEY_LEFT)) {
            auto [x, _] = Basic(hero->stepForce, 180).vector();
            hero->resultantForce.x += x;
            hero->side = LEFT;
            if (isGrounded) hero->isWalking = true;
        }
    };

    isWalking = false;
    if (bool grounded = isGrounded()) {
        // jumping
        if (IsKeyDown(KEY_UP)) {
            auto [_, y] = Basic(jumpForce, 90).vector();
            resultantForce.y += y;
        }

        // squatting
        if (IsKeyDown(KEY_DOWN) && !isSquatting) {
            position.y  = screenHeight - radius;
            isSquatting = true;
        }
        if (!IsKeyDown(KEY_DOWN) && isSquatting) {
            position.y  = screenHeight - radius;
            isSquatting = false;
        }

        // left/right
        if (!isSquatting) {
            leftRightMovement(this, grounded);
        } else {
            if (IsKeyDown(KEY_RIGHT)) side = RIGHT;
            if (IsKeyDown(KEY_LEFT)) side = LEFT;
        }
    } else {
        // left/right - in air
        leftRightMovement(this, grounded);
    }
}

SpriteDef Hero::getSprite() {
    if (isGrounded()) {
        if (framesToLand > 0) {
            framesToLand--;
            return SpriteDef {type, LAND, side};
        }
        if (framesToTurn > 0) {
            framesToTurn--;
            return SpriteDef {type, TURN, side};
        }

        if (previousSide != side) {
            previousSide = side;
            framesToTurn = initialFramesToTurn;
            return SpriteDef {type, TURN, side};
        }
        if (isSquatting) return SpriteDef {type, SQUAT, side};
        if (isWalking) return SpriteDef {type, WALK, side};
    } else {
        if (velocity.y <= 0) {
            framesToLand = initialFramesToLand;
            return SpriteDef {type, JUMP, side};
        }
        if (velocity.y > 0) return SpriteDef {type, FALL, side};
    }
    return SpriteDef {type, IDLE, side};
}