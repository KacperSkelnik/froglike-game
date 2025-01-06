//
// Created by Kacper Skelnik on 09.12.2024.
//

#ifndef ENEMY_H
#define ENEMY_H
#include "../animation/animation.h"
#include "object.h"

class Enemy final: public Object {
  private:
    int      frameCount = 0;
    float    stepForce;
    float    jumpForce;
    Vector2* heroPosition;

    ObjectSide side = RIGHT;

    const int initialFramesToLand = 16;
    int       framesToLand        = 0;
    const int initialFramesToTurn = 32;
    int       framesToTurn        = 0;

    SpriteDef getSprite() override;

  public:
    Enemy(
        Animation* animation,
        TileMap*   tileMap,
        ObjectType type,
        Vector2*   heroPosition
    );
    void applyForces(const float* deltaTime) override;
    void move() override;
};

#endif // ENEMY_H
