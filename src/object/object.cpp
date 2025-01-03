//
// Created by Kacper Skelnik on 09.12.2024.
//

#include "object.h"

#include "../force/force.h"

void Object::checkCollisions() {
    const Rectangle objectsRect = getRectangle();
    isGrounded                  = false;
    bool wallDetected           = false;
    for (const Rectangle& rectangle : tileMap->getGrounds()) {
        if (CheckCollisionRecs(rectangle, objectsRect)) {
            const bool isOverTheRect = screenHeight - rectangle.y <=
                                       screenHeight - objectsRect.y - objectsRect.height + rectangle.height;

            // check if object is on the ground
            if (isOverTheRect && !isGrounded) {
                float overlaps;
                if (rectangle.x < objectsRect.x) overlaps = rectangle.width - (objectsRect.x - rectangle.x);
                else overlaps = objectsRect.width - (rectangle.x - objectsRect.x);

                if (overlaps > 0.3 * width) {
                    velocity.y = 0;
                    position.y = rectangle.y - height;
                    isGrounded = true;
                }
            }
            // check if object is under the platform
            if (!isOverTheRect && rectangle.y < objectsRect.y) {
                velocity.y = 0;
                velocity.x = 0;
            }
            // handle walls
            else if (!isOverTheRect && !wallDetected) {
                velocity.x   = 0;
                wallDetected = true;
                if (rectangle.x + rectangle.width - objectsRect.x > objectsRect.x - rectangle.x + rectangle.width) {
                    position.x = rectangle.x - objectsRect.width;
                } else {
                    position.x = rectangle.x + rectangle.width;
                }
            }
            // Nothing else to check
            if (isGrounded && wallDetected) break;
        }
    }
}

void Object::pushAwayFromTheRoof() {
    if (const float center = position.y; center <= 0) {
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

    checkCollisions();
}

void Object::restartForces() {
    resultantForce = gravity;
}

void Object::draw() {
    applyForces();
    animation->animate(getSprite(), getRectangle());
    restartForces();
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
    animation(animation),
    tileMap(tileMap) {}
