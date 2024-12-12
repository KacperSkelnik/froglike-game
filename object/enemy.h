//
// Created by Kacper Skelnik on 09.12.2024.
//

#ifndef ENEMY_H
#define ENEMY_H
#include "object.h"

class Enemy final: public Object {
  private:
    float    stepForce;
    float    jumpForce;
    Vector2 &heroPosition;

  public:
    Enemy(float screenWidth, float screenHeight, Vector2 &heroPosition);
    void move() override;
    void draw() override;
};

#endif // ENEMY_H
