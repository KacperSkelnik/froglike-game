//
// Created by Kacper Skelnik on 04.12.2024.
//

#ifndef HERO_H
#define HERO_H
#include <raylib.h>
#include "object.h"

class Hero final : public Object {
    private:
        float stepForce;
        float jumpForce;
        bool isSquatting;

    public:
        Hero(float screenWidth, float screenHeight);
        void move() override;
        void draw() override;
};

#endif //HERO_H
