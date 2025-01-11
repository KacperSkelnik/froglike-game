//
// Created by Kacper Skelnik on 04.12.2024.
//

#ifndef HERO_H
#define HERO_H
#include "../camera/camera.h"
#include "collisions.h"
#include "drawable.h"
#include "movable.h"

class Hero final: public Drawable, Movable {
  private:
    GameCamera* camera;
    Collisions  collisions;

    ObjectType type = HERO;

    float stepForce;
    float jumpForce;
    bool  isSquatting = false;
    bool  isWalking   = false;

    const int initialFramesToLand = 16;
    int       framesToLand        = 0;
    const int initialFramesToTurn = 8;
    int       framesToTurn        = 0;

    ObjectSide previousSide = LEFT;
    ObjectSide side         = RIGHT;

    SpriteDef getSprite() override;

  public:
    Hero(
        Animation*  animation,
        TileMap*    tileMap,
        GameCamera* camera
    );
    void applyForces(const float* deltaTime) override;
    void move() override;
    void updatePosition(
        float mapWidth,
        float mapHeight
    );
    [[nodiscard]] Vector2 getPosition() const;
};

#endif // HERO_H
