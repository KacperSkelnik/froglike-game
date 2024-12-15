//
// Created by Kacper Skelnik on 13.12.2024.
//

#include "animation.h"

#include <ranges>

Sprite Animation::loadSprite(
    const char* path,
    const int   number
) const {
    Sprite sprite          = Sprite();
    sprite.framesNumber    = number;
    sprite.framesPerSecond = 20;

    auto* images   = static_cast<Image*>(malloc(sizeof(Image) * number));
    auto* textures = static_cast<Texture2D*>(malloc(sizeof(Texture2D) * number));

    for (int i = 0; i < number; i++) {
        char fullPath[256];
        snprintf(fullPath, 256, "%s/%s_%d.png", basePath, path, i);
        images[i]   = LoadImage(fullPath);
        textures[i] = LoadTextureFromImage(images[i]);
    }

    sprite.images   = images;
    sprite.textures = textures;

    return sprite;
}

void Animation::draw(
    const Sprite*  sprite,
    const int*     frameCount,
    const Vector2* position,
    const float    scale
) {
    int frame_number = *frameCount % (sprite->framesNumber * sprite->framesPerSecond) / sprite->framesPerSecond;
    if (frame_number >= sprite->framesNumber) {
        frame_number = 0;
    }

    // clang-format off
    DrawTexturePro(
        sprite->textures[frame_number],
        Rectangle {0, 0, 32, 32},
        Rectangle {position->x - 100, position->y - 100, 32 * scale, 32 * scale},
        Vector2 {0, 0},
        0,
        WHITE)
    ;
    // clang-format on
}

void Animation::animate(
    SpriteDef      sprite,
    const int*     frameCount,
    const Vector2* position,
    const float    scale
) {
    if (this->sprites.contains(sprite)) {
        const std::shared_ptr<Sprite> loaded = this->sprites[sprite];
        draw(loaded.get(), frameCount, position, scale);
    } else {
        Sprite                  loaded  = loadSprite(sprite.path, sprite.framesNumber);
        std::shared_ptr<Sprite> pointer = std::make_shared<Sprite>(loaded);
        this->sprites.emplace(sprite, pointer);
        draw(pointer.get(), frameCount, position, scale);
    }
}
