//
// Created by Kacper Skelnik on 09.12.2024.
//

#include "enemy.h"
#include <iostream>
#include <numbers>
#include <random>

Enemy::Enemy(const float screenWidth, const float screenHeight, Vector2 &heroPosition): stepForce(1), jumpForce(-25), heroPosition(heroPosition) {
    this->radius       = 50;
    this->mass         = 1;
    this->gravity      = Gravity(mass).vector();
    this->screenWidth  = screenWidth;
    this->screenHeight = screenHeight;

    std::random_device              sd {};
    std::mt19937                    engine {sd()};
    std::uniform_int_distribution<> distribution(static_cast<int>(radius), static_cast<int>(screenWidth - radius));
    this->position = Vector2(static_cast<float>(distribution(engine)), screenHeight - radius);
}

void Enemy::move() {
    const float dx    = position.x - heroPosition.x;
    const float dy    = position.y - heroPosition.y;
    const float angle = 180 - static_cast<float>(atan2(dy, dx) * 180.0f / std::numbers::pi);
    Vector2     force = {0, 0};
        if (isGrounded()) {
                if (0 < angle && angle <= 90) {
                    force = Basic(jumpForce, 135).vector();
                } else if (90 < angle && angle <= 180) {
                    force = Basic(jumpForce, 45).vector();
            }
        } else {
                if (90 <= angle && angle < 270) {
                    force = Basic(stepForce, 180).vector();
                } else if ((270 <= angle && angle <= 360) || (0 <= angle && angle < 90)) {
                    force = Basic(stepForce, 0).vector();
            }
        }
    resultantForce.x += force.x;
    resultantForce.y += force.y;
}

void Enemy::draw() {
    applyForces();
    DrawCircleV(position, radius, BROWN);
    restartForces();
}
