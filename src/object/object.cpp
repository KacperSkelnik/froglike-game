//
// Created by Kacper Skelnik on 09.12.2024.
//

#include "object.h"

#include "../force/force.h"

// void Object::detectWalls() {
//     isGrounded        = false;
//     bool wallDetected = false;
//     for (const Rectangle& rectangle : tileMap->getGrounds()) {
//         if (CheckCollisionRecs(rectangle, getRectangle())) {
//             const bool isOverTheRect = static_cast<float>(GetScreenHeight()) - rectangle.y <=
//                                        static_cast<float>(GetScreenHeight()) - position.y - height + rectangle.height;
//
//             float overlaps;
//             if (rectangle.x < position.x) overlaps = rectangle.width - (position.x - rectangle.x);
//             else overlaps = width - (rectangle.x - position.x);
//
//             // check if object is on the ground
//             if (isOverTheRect && !isGrounded && overlaps > 0.3 * width) {
//                 velocity.y = 0;
//                 position.y = rectangle.y - height;
//                 isGrounded = true;
//             }
//             // check if object is under the platform
//             if (!isOverTheRect && rectangle.y < position.y && overlaps > 0.3 * width) {
//                 velocity.y       = 0;
//                 resultantForce.y = gravity.y;
//                 position.y       = rectangle.y + rectangle.height;
//             }
//             // handle walls
//             else if (!isOverTheRect && !wallDetected) {
//                 wallDetected = true;
//                 Vector2 force;
//                 if (rectangle.x + rectangle.width - position.x > position.x - rectangle.x + rectangle.width) {
//                     force = Basic(position.x + width - rectangle.x, 180).vector();
//                 } else {
//                     force = Basic(rectangle.x + rectangle.width - position.x, 0).vector();
//                 }
//                 resultantForce.x += force.x;
//             }
//         }
//     }
// }

void Object::applyResistance() {
    auto [xResistance, _] = Resistance(velocity, 0.3).vector();
    velocity.x += xResistance;
}

void Object::applyGravity() {
    if (!isGrounded) resultantForce.y = gravity.y;
}

Rectangle Object::getRectangle() const {
    return {position.x, position.y, width, height};
}

void Object::draw() {
    animation->animate(getSprite(), getRectangle());
}

Object::Object(
    Animation*       animation,
    TileMap*         tileMap,
    const ObjectType type,
    float            scaleX,
    float            scaleY,
    const float      mass
):
    type(type),
    scaleX(scaleX),
    scaleY(scaleY),
    mass(mass),
    animation(animation),
    tileMap(tileMap) {}
