//
// Created by Kacper Skelnik on 05.01.2025.
//

#include "collisions.h"

Collisions::Collisions(TileMap* tileMap): tileMap(tileMap) {
    CollisionsRegister _register = CollisionsRegister();
    _register.reset();
    collisionsRegister = _register;
}

void Collisions::detectGround(
    const Rectangle rectangle,
    const Rectangle referenceRect,
    const float     overlaps
) {
    if (overlaps > 0.3 * referenceRect.width) {
        collisionsRegister.ground  = true;
        collisionsRegister.groundY = rectangle.y;
    }
}

void Collisions::detectCeiling(
    const Rectangle rectangle,
    const Rectangle referenceRect,
    const float     overlaps
) {
    if (rectangle.y <= referenceRect.y && overlaps > 0.3 * referenceRect.width) {
        collisionsRegister.ceiling  = true;
        collisionsRegister.ceilingY = rectangle.y + rectangle.height;
    }
}

void Collisions::detectWalls(
    const Rectangle rectangle,
    const Rectangle referenceRect,
    const float     overlaps
) {
    if (rectangle.y + rectangle.height / 1.5 < referenceRect.y + referenceRect.height) {
        if (rectangle.x + rectangle.width - referenceRect.x > referenceRect.x - rectangle.x + rectangle.width) {
            collisionsRegister.rightWall = true;
        } else {
            collisionsRegister.leftWall = true;
        }
        collisionsRegister.overlaps = overlaps;
    }
}

bool Collisions::checkCollisions(
    const Rectangle rec1,
    const Rectangle rec2
) {
    // clang-format off
    if (
        (rec1.x <= (rec2.x + rec2.width) &&
        (rec1.x + rec1.width) >= rec2.x) &&
        (rec1.y <= (rec2.y + rec2.height) &&
        (rec1.y + rec1.height) >= rec2.y)
    ) return true;
    // clang-format on
    return false;
}

void Collisions::detect(const Rectangle referenceRect) {
    collisionsRegister.reset();

    for (const Rectangle& rectangle : tileMap->getGrounds()) {
        if (checkCollisions(rectangle, referenceRect)) {
            const bool isOverTheRect = rectangle.y + rectangle.height >= referenceRect.y + referenceRect.height;

            float overlaps;
            if (rectangle.x < referenceRect.x) overlaps = rectangle.width - (referenceRect.x - rectangle.x);
            else overlaps = referenceRect.width - (rectangle.x - referenceRect.x);

            if (isOverTheRect && !collisionsRegister.ground) detectGround(rectangle, referenceRect, overlaps);
            if (!isOverTheRect && !collisionsRegister.ceiling) detectCeiling(rectangle, referenceRect, overlaps);
            if (!collisionsRegister.leftWall || !collisionsRegister.rightWall) {
                detectWalls(rectangle, referenceRect, overlaps);
            }
        }
    }
}

CollisionsRegister Collisions::getRegister() const {
    return collisionsRegister;
}