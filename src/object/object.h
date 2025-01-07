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

    float mass;

    Vector2 gravity = Gravity(mass).vector();
    Vector2 resultantForce {0, 0};
    Vector2 velocity {0, 0};

    bool isGrounded = false;

    void applyResistance();
    void applyGravity();

  public:
    explicit Object(
        ObjectType type,
        float      mass
    );
    virtual ~Object() = default;
    virtual void applyForces(const float* deltaTime) {};
    virtual void move() {};
};

#endif // OBJECT_H
