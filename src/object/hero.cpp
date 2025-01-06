//
// Created by Kacper Skelnik on 05.12.2024.
//
#include "hero.h"

#include "../force/force.h"

Hero::Hero(
    Animation*  animation,
    TileMap*    tileMap,
    GameCamera* camera
):
    Object(
        animation,
        tileMap,
        ObjectType::HERO,
        6,
        6,
        3
    ),
    camera(camera),
    collisions(Collisions(tileMap)),
    stepForce(12.0f),
    jumpForce(-26.0f) {

    this->gravity         = Gravity(mass).vector();
    this->position        = Vector2(GetScreenWidth() / 2, GetScreenHeight() - 9 * height);
    camera->camera.target = this->position;
}

void Hero::move() {
    auto leftRightMovement = [](Hero* hero, const bool isGrounded) -> void {
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
    if (isGrounded) {
        // jumping
        if (IsKeyDown(KEY_UP)) {
            auto [_, y] = Basic(jumpForce, 90).vector();
            resultantForce.y += y;
        }

        // squatting
        if (IsKeyDown(KEY_DOWN) && !isSquatting) isSquatting = true;
        if (!IsKeyDown(KEY_DOWN) && isSquatting) isSquatting = false;

        // left/right
        if (!isSquatting) {
            leftRightMovement(this, isGrounded);
        } else {
            if (IsKeyDown(KEY_RIGHT)) side = RIGHT;
            if (IsKeyDown(KEY_LEFT)) side = LEFT;
        }
    } else {
        // left/right - in air
        leftRightMovement(this, isGrounded);
    }
}

SpriteDef Hero::getSprite() {
    if (isGrounded) {
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

void Hero::applyForces(const float* deltaTime) {
    // This function moves camera rather than the hero itself

    // Collisions
    collisions.detect(getRectangle());
    const CollisionsRegister _register = collisions.getRegister();
    isGrounded                         = _register.ground;

    // Walls push back
    if (_register.leftWall && _register.overlaps) {
        resultantForce.x += Basic(_register.overlaps.value() / 1.8, 0).vector().x;
    }
    if (_register.rightWall && _register.overlaps) {
        resultantForce.x += Basic(_register.overlaps.value() / 1.8, 180).vector().x;
    }

    // External forces
    applyGravity();
    applyResistance();

    // Force into velocity
    const float accelerationX = resultantForce.x / mass;
    velocity.x += accelerationX * *deltaTime * 0.5f;
    camera->camera.target.x += velocity.x * *deltaTime;
    velocity.x += accelerationX * *deltaTime * 0.5f;

    const float accelerationY = resultantForce.y / mass;
    velocity.y += accelerationY * *deltaTime * 0.5f;
    camera->camera.target.y += velocity.y * *deltaTime;
    velocity.y += accelerationY * *deltaTime * 0.5f;

    // Fround and ceiling adjustments
    if (_register.ground && _register.groundY && velocity.y > 0) {
        velocity.y              = 0;
        resultantForce.y        = 0;
        camera->camera.target.y = _register.groundY.value();
    }
    if (_register.ceiling && _register.ceilingY && velocity.y < 0) {
        velocity.y              = 0;
        resultantForce.y        = gravity.y;
        camera->camera.target.y = _register.ceilingY.value() + height;
    }

    // Position update
    position.x = camera->camera.offset.x - width;
    position.y = camera->camera.offset.y - height;

    // don't remove!
    resultantForce.x = 0;
}

bool Hero::getGrounded() const {
    return isGrounded;
}