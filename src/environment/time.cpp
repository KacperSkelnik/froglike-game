//
// Created by Kacper Skelnik on 03.01.2025.
//

#include "time.h"

Time::Time(const int targetFPS): targetFPS(targetFPS) {}

float Time::deltaTime() {
    double       currentTime    = GetTime();
    const double updateDrawTime = currentTime - previousTime;

    if (targetFPS > 0) {
        const double waitTime = (1.0f / static_cast<float>(targetFPS)) - updateDrawTime;
        if (waitTime > 0) {
            WaitTime(static_cast<float>(waitTime));
            currentTime = GetTime();
            delta       = static_cast<float>(currentTime - previousTime);
        }
    } else {
        delta = static_cast<float>(updateDrawTime);
    }

    previousTime = currentTime;

    return delta * 50;
}