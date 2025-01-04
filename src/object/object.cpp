//
// Created by Kacper Skelnik on 09.12.2024.
//

#include "object.h"

#include "../force/force.h"

void Object::checkCollisions() {
    isGrounded        = false;
    bool wallDetected = false;
    for (const Rectangle& rectangle : tileMap->getGrounds()) {
        if (CheckCollisionRecs(rectangle, getRectangle())) {
            const bool isOverTheRect = GetScreenHeight() - rectangle.y <=
                                       GetScreenHeight() - position.y - height + rectangle.height;

            float overlaps;
            if (rectangle.x < position.x) overlaps = rectangle.width - (position.x - rectangle.x);
            else overlaps = width - (rectangle.x - position.x);

            // check if object is on the ground
            if (isOverTheRect && !isGrounded) {
                if (overlaps > 0.3 * width) {
                    velocity.y = 0;
                    position.y = rectangle.y - height;
                    isGrounded = true;
                }
            }
            // check if object is under the platform
            if (!isOverTheRect && rectangle.y < position.y && overlaps > 0.5 * width) {
                velocity.y       = 0;
                resultantForce.y = gravity.y;
                position.y       = rectangle.y + rectangle.height;
            }
            // handle walls
            else if (!isOverTheRect && !wallDetected) {
                wallDetected = true;
                Vector2 force;
                if (rectangle.x + rectangle.width - position.x > position.x - rectangle.x + rectangle.width) {
                    force = Basic(position.x + width - rectangle.x, 180).vector();
                } else {
                    force = Basic(rectangle.x + rectangle.width - position.x, 0).vector();
                }
                resultantForce.x += force.x;
            }
        }
    }
}

void Object::applyResistance() {
    auto [xResistance, _] = Resistance(velocity, 0.2).vector();
    velocity.x += xResistance;
}

void Object::applyGravity() {
    if (!isGrounded) resultantForce.y = gravity.y;
}

void Object::applyForces(const float* deltaTime) {
    applyGravity();
    checkCollisions();
    applyResistance();

    const float accelerationX = resultantForce.x / mass;
    velocity.x += accelerationX * *deltaTime * 0.5f;
    position.x += velocity.x * *deltaTime;
    velocity.x += accelerationX * *deltaTime * 0.5f;

    const float accelerationY = resultantForce.y / mass;
    velocity.y += accelerationY * *deltaTime * 0.5f;
    position.y += velocity.y * *deltaTime;
    velocity.y += accelerationY * *deltaTime * 0.5f;

    // don't remove!
    resultantForce.x = 0;
}

void Object::draw(const float* deltaTime) {
    applyForces(deltaTime);
    animation->animate(getSprite(), getRectangle());
}

Rectangle Object::getRectangle() const {
    return {position.x, position.y, width, height};
}

Object::Object(
    Animation*       animation,
    TileMap*         tileMap,
    const ObjectType type,
    const float      width,
    const float      height,
    const float      mass
):
    type(type),
    height(height),
    width(width),
    mass(mass),
    animation(animation),
    tileMap(tileMap) {}
