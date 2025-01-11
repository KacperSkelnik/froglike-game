//
// Created by Kacper Skelnik on 11.01.2025.
//

#ifndef MOVABLE_H
#define MOVABLE_H
#include "../force/force.h"
#include "raylib.h"

class Movable {
  protected:
    float   mass;
    Vector2 gravity = Gravity(mass).vector();
    Vector2 resultantForce {0, 0};
    Vector2 velocity {0, 0};
    bool    isGrounded = false;

    void applyResistance();
    void applyGravity();

  public:
    explicit Movable(float mass);
    virtual ~Movable() = default;
    virtual void applyForces(const float* deltaTime) {};
    virtual void move() {};
};

#endif // MOVABLE_H
