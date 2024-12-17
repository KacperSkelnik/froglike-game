//
// Created by Kacper Skelnik on 09.12.2024.
//

#ifndef ENEMY_H
#define ENEMY_H
#include "../animation/animation.h"
#include "object.h"

class Enemy final: public Object {
  private:
    float    stepForce;
    float    jumpForce;
    Vector2* heroPosition;

    ObjectSide side = RIGHT;

    const int initialFramesToLand = 8;
    int       framesToLand        = 0;
    const int initialFramesToTurn = 32;
    int       framesToTurn        = 0;

    SpriteDef getSprite() override;

  public:
    Enemy(
        Animation* animation,
        ObjectType type,
        float      screenWidth,
        float      screenHeight,
        Vector2*   heroPosition,
        int*       frameCount
    );
    void move() override;
};

#endif // ENEMY_H
