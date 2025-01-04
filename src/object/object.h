//
// Created by Kacper Skelnik on 09.12.2024.
//

#ifndef OBJECT_H
#define OBJECT_H
#include "../animation/animation.h"
#include "../environment/tilemap.h"
#include "../force/force.h"
#include "type.h"
#include <raylib.h>

class Object {
  protected:
    ObjectType type;

    float height;
    float width;
    float mass;

    ObjectSide previousSide = NONE;

    Vector2 gravity = Gravity(mass).vector();
    Vector2 resultantForce {0, 0};
    Vector2 velocity {0, 0};

    bool isGrounded = false;

    Animation* animation;
    TileMap*   tileMap;

    void                    checkCollisions();
    void                    applyResistance();
    void                    applyGravity();
    void                    applyForces(const float* deltaTime);
    virtual SpriteDef       getSprite() = 0;
    [[nodiscard]] Rectangle getRectangle() const;

  public:
    explicit Object(
        Animation* animation,
        TileMap*   tileMap,
        ObjectType type,
        float      width,
        float      height,
        float      mass
    );
    virtual ~Object() = default;
    Vector2 position {};

    void draw(const float* deltaTime);

    virtual void move() {};
};

#endif // OBJECT_H
