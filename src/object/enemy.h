//
// Created by Kacper Skelnik on 09.12.2024.
//

#ifndef ENEMY_H
#define ENEMY_H
#include "../animation/animation.h"
#include "../environment/tilemap.h"
#include "collisions.h"
#include "drawable.h"
#include "movable.h"

class Enemy final: public Drawable, Movable {
  private:
    GameCamera* camera;
    Collisions  collisions;

    ObjectType type;

    Vector2 mapPosition {};

    int   frameCount = 0;
    float stepForce;
    float jumpForce;

    ObjectSide previousSide = RIGHT;
    ObjectSide side         = RIGHT;

    const int initialFramesToLand = 16;
    int       framesToLand        = 0;
    const int initialFramesToTurn = 32;
    int       framesToTurn        = 0;

    SpriteDef getSprite() override;
    bool      isOnTheScreen() const;

  public:
    Enemy(
        ObjectType  type,
        Animation*  animation,
        TileMap*    tileMap,
        GameCamera* camera
    );
    void applyForces(const float* deltaTime) override;
    void move() override;
    void updatePosition();
};

#endif // ENEMY_H
