//
// Created by Kacper Skelnik on 04.12.2024.
//

#ifndef HERO_H
#define HERO_H
#include "object.h"

class Hero final: public Object {
  private:
    float stepForce;
    float jumpForce;
    bool  isSquatting = false;
    bool  isWalking   = false;

    const int initialFramesToLand = 16;
    int       framesToLand        = 0;
    const int initialFramesToTurn = 8;
    int       framesToTurn        = 0;

    ObjectSide previousSide = RIGHT;
    ObjectSide side         = RIGHT;

    SpriteDef getSprite() override;

  public:
    Hero(
        Animation* animation,
        ObjectType type,
        float      screenWidth,
        float      screenHeight
    );
    void move() override;
};

#endif // HERO_H
