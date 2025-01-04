//
// Created by Kacper Skelnik on 03.01.2025.
//

#ifndef TIME_H
#define TIME_H
#include "raylib.h"

class Time {
  private:
    double previousTime = GetTime();
    int    targetFPS;
    float  delta = 0;

  public:
    explicit Time(int targetFPS);
    float deltaTime();
};

#endif // TIME_H
