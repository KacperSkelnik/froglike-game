//
// Created by Kacper Skelnik on 05.01.2025.
//

#include "camera.h"

#include <iostream>

GameCamera::GameCamera():
    screenWidth(static_cast<float>(GetScreenWidth())),
    screenHeight(static_cast<float>(GetScreenHeight())),
    camera({}) {
    Camera2D camera;
    camera.target   = {screenWidth / 2.0f, screenHeight / 2.0f};
    camera.offset   = {screenWidth / 2.0f, screenHeight / 2.0f};
    camera.rotation = 0.0f;
    camera.zoom     = 1.0f;

    this->camera = camera;
}

void GameCamera::updateVertically(const float mapWidth) {
    if (camera.target.x <= screenWidth / 2) { // left wall
        camera.offset.x = camera.target.x;
    } else if (camera.target.x >= mapWidth - screenWidth / 2) { // right wall
        camera.offset.x = screenWidth - (mapWidth - camera.target.x);
    } else {
        camera.offset.x = screenWidth / 2;
    }
}

void GameCamera::updateHorizontally(const float mapHeight) {
    if (camera.target.y >= screenHeight / 2) {
        camera.offset.y = camera.target.y;
    } else {
        camera.offset.y = screenHeight / 2;
    }
}

void GameCamera::updateOffset(
    const float mapWidth,
    const float mapHeight
) {
    updateVertically(mapWidth);
    updateHorizontally(mapHeight);
}