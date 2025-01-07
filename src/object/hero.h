//
// Created by Kacper Skelnik on 04.12.2024.
//

#ifndef HERO_H
#define HERO_H
#include "../camera/camera.h"
#include "collisions.h"
#include "drawable.h"
#include "object.h"

class Hero final: public Drawable, Object {
  private:
    GameCamera* camera;
    Collisions  collisions;

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
        Animation*  animation,
        TileMap*    tileMap,
        GameCamera* camera
    );
    void applyForces(const float* deltaTime) override;
    void updatePosition(
        float mapWidth,
        float mapHeight
    );
    void move() override;
};

#endif // HERO_H
