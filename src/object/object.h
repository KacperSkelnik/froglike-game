//
// Created by Kacper Skelnik on 09.12.2024.
//

#ifndef OBJECT_H
#define OBJECT_H
#include "../animation/animation.h"
#include "../force/force.h"
#include "type.h"
#include <raylib.h>

class Object {
  private:
    ObjectType type;

  protected:
    float radius;
    float mass;
    float screenWidth;
    float screenHeight;

    Vector2 gravity = Gravity(mass).vector();
    Vector2 resultantForce {};
    Vector2 velocity {};

    Animation* animation;

    [[nodiscard]] bool      isGrounded() const;
    void                    keepGrounded();
    void                    pushAwayFromTheRoof();
    void                    pushAwayFromTheLeftWall();
    void                    pushAwayFromTheRightWall();
    void                    applyAirResistance();
    void                    applyForces();
    void                    restartForces();
    [[nodiscard]] SpriteDef getSprite() const;

  public:
    explicit Object(
        Animation* animation,
        ObjectType type,
        float      radius,
        float      mass,
        float      screenWidth,
        float      screenHeight
    );
    virtual ~Object() = default;
    Vector2 position {};

    virtual void move() {};
    virtual void draw() {};
};

#endif // OBJECT_H
