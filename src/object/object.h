//
// Created by Kacper Skelnik on 09.12.2024.
//

#ifndef OBJECT_H
#define OBJECT_H
#include "../force.h"
#include <raylib.h>

class Object {
  protected:
    float radius       = 0;
    float mass         = 0;
    float screenWidth  = 0;
    float screenHeight = 0;

    Vector2 gravity = Gravity(mass).vector();
    Vector2 resultantForce {};
    Vector2 velocity {};

    [[nodiscard]] bool isGrounded() const;
    void               keepGrounded();
    void               pushAwayFromTheRoof();
    void               pushAwayFromTheLeftWall();
    void               pushAwayFromTheRightWall();
    void               applyAirResistance();
    void               applyForces();
    void               restartForces();

  public:
    virtual ~Object() = default;
    Vector2 position {};

    virtual void move() {};
    virtual void draw() {};
};

#endif // OBJECT_H
