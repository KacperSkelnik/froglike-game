//
// Created by Kacper Skelnik on 05.12.2024.
//

#ifndef FORCE_H
#define FORCE_H
#include "raylib.h"

class Force {
  public:
    virtual ~Force() = default;
    virtual Vector2 vector() { return Vector2(0, 0); };
};

class Gravity final: public Force {
  private:
    float mass;

  public:
    explicit Gravity(float mass);
    [[nodiscard]] Vector2 vector() override;
};

class Basic final: public Force {
  private:
    float newtons;
    float angle;

  public:
    explicit Basic(float newtons, float angle);
    [[nodiscard]] Vector2 vector() override;
};

class AirResistance final: public Force {
  private:
    Vector2 resultantForce;
    float   factor;

  public:
    explicit AirResistance(Vector2 resultantForce, float factor);
    [[nodiscard]] Vector2 vector() override;
};

#endif // FORCE_H
