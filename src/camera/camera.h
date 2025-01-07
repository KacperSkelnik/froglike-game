//
// Created by Kacper Skelnik on 05.01.2025.
//

#ifndef CAMERA_H
#define CAMERA_H
#include "raylib.h"

class GameCamera {
  private:
    float screenWidth;
    float screenHeight;

    void updateVertically(float mapWidth);
    void updateHorizontally(float mapHeight);

  public:
    Camera2D camera;

    explicit GameCamera();
    void updateOffset(
        float mapWidth,
        float mapHeight
    );
};

#endif // CAMERA_H
