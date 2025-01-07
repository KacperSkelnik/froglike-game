//
// Created by Kacper Skelnik on 07.01.2025.
//

#include "drawable.h"

Drawable::Drawable(
    Animation* animation,
    float      width,
    float      height
):
    animation(animation),
    width(width),
    height(height) {}

Rectangle Drawable::getRectangle() const {
    return {position.x, position.y, width, height};
}

void Drawable::draw() {
    animation->animate(getSprite(), getRectangle());
}
