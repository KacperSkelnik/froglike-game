//
// Created by Kacper Skelnik on 09.12.2024.
//

#include "enemy.h"

#include "../force/force.h"
#include <numbers>
Enemy::Enemy(
    const ObjectType type,
    Animation*       animation,
    TileMap*         tileMap,
    GameCamera*      camera
):
    Drawable(
        animation,
        16 * 3,
        16 * 3
    ),
    Movable(2),
    camera(camera),
    collisions(Collisions(tileMap)),
    type(type),
    stepForce(6),
    jumpForce(-30) {

    const auto  initialX = static_cast<float>(GetScreenWidth()) / 2;
    const float initialY = static_cast<float>(GetScreenHeight()) - 2 * height;
    this->mapPosition    = Vector2(initialX, initialY);
}

void Enemy::move() {
    if (isOnTheScreen()) {
        frameCount++;
        if (!isGrounded || frameCount % 100 == 0) {
            Vector2 force = {0, 0};
            if (isGrounded && framesToLand == 0 && framesToTurn == 0) {
                const float dx    = mapPosition.x - camera->camera.target.x;
                const float dy    = mapPosition.y - camera->camera.target.y;
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
}

SpriteDef Enemy::getSprite() {
    if (isGrounded) {
        if (framesToLand > 0) {
            framesToLand--;
            return SpriteDef {type, LAND, side};
        }
        if (framesToTurn > 0) {
            framesToTurn--;
            return SpriteDef {type, TURN, NONE};
        }

        const float dx = mapPosition.x - camera->camera.target.x;
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

bool Enemy::isOnTheScreen() const {
    if (camera->camera.target.x - camera->camera.offset.x > mapPosition.x ||
        camera->camera.target.x - camera->camera.offset.x + static_cast<float>(GetScreenWidth()) < mapPosition.x)
        return false;

    if (camera->camera.target.y - camera->camera.offset.y + static_cast<float>(GetScreenHeight()) < mapPosition.y)
        return false;

    return true;
}

void Enemy::applyForces(const float* deltaTime) {
    if (isOnTheScreen()) {
        // External forces
        applyGravity();
        applyResistance();

        // Collisions
        collisions.detect(getRectangle());
        const CollisionsRegister _register = collisions.getRegister();

        // Walls push back
        if (_register.leftWall && _register.overlaps) {
            resultantForce.x += Basic(_register.overlaps.value(), 0).vector().x;
        }
        if (_register.rightWall && _register.overlaps) {
            resultantForce.x += Basic(_register.overlaps.value(), 180).vector().x;
        }

        const float accelerationX = resultantForce.x / mass;
        velocity.x += accelerationX * *deltaTime * 0.5f;
        mapPosition.x += velocity.x * *deltaTime;
        velocity.x += accelerationX * *deltaTime * 0.5f;

        const float accelerationY = resultantForce.y / mass;
        velocity.y += accelerationY * *deltaTime * 0.5f;
        // Ground and ceiling adjustments
        if (_register.ground && _register.groundY && velocity.y > 0) {
            mapPosition.y = _register.groundY.value() + (camera->camera.target.y - camera->camera.offset.y);
            velocity.y    = 0;
        } else if (_register.ceiling && _register.ceilingY && velocity.y < 0) {
            mapPosition.y = _register.ceilingY.value() + (camera->camera.target.y - camera->camera.offset.y) + height;
            velocity.y    = 0;
            resultantForce.y = gravity.y;
        } else {
            mapPosition.y += velocity.y * *deltaTime;
            velocity.y += accelerationY * *deltaTime * 0.5f;
        }

        isGrounded = _register.ground;

        // don't remove!
        resultantForce.x = 0;
    }
}

void Enemy::updatePosition() {
    position.x = mapPosition.x + (camera->camera.offset.x - camera->camera.target.x) - width / 2;
    position.y = mapPosition.y + (camera->camera.offset.y - camera->camera.target.y) - height;
}