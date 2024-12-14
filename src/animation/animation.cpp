//
// Created by Kacper Skelnik on 13.12.2024.
//

#include "animation.h"

#include <iostream>
#include <string>

inline const char* toString(const Kind kind) {
    switch (kind) {
        case DEATH:
            return "death";
        case HURT:
            return "hurt";
        case IDLE:
            return "idle";
        case FALL:
            return "fall";
        case JUMP:
            return "jump";
        case LAND:
            return "land";
        case TURN:
            return "idle";
        default:
            return "[Unknown Kind]";
    }
}

inline const char* toString(const Side side) {
    switch (side) {
        case LEFT:
            return "left";
        case RIGHT:
            return "right";
        default:
            return "[Unknown Side]";
    }
}

Sprite Animation::load_sprite(
    const char*               name,
    const Kind                kind,
    const int                 number,
    const std::optional<Side> side
) {
    Sprite sprite            = Sprite();
    sprite.frames            = number;
    sprite.frames_per_second = 7;

    auto* images   = static_cast<Image*>(malloc(sizeof(Image) * number));
    auto* textures = static_cast<Texture2D*>(malloc(sizeof(Texture2D) * number));

    for (int i = 0; i < number; i++) {
        char        path[256];
        const char* stringifyKind = toString(kind);
        char        stringifySide[8];
        if (side.has_value()) snprintf(stringifySide, 8, "_%s", toString(side.value()));
        else stringifySide[0] = ""[0];

        snprintf(path, 256, "../assets/animations/%s/%s/%s%s_%d.png", name, stringifyKind, stringifyKind, stringifySide, i);
        images[i]   = LoadImage(path);
        textures[i] = LoadTextureFromImage(images[i]);
    }

    sprite.images   = images;
    sprite.textures = textures;

    return sprite;
}
void Animation::animate(
    const Sprite*  sprite,
    const int      frameCount,
    const Vector2* position,
    const float    scale
) {
    int frame_number = (frameCount % (sprite->frames * sprite->frames_per_second)) / sprite->frames_per_second;
    if (frame_number >= sprite->frames) {
        frame_number = 0;
    }

    // clang-format off
    DrawTexturePro(
        sprite->textures[frame_number],
        Rectangle {0, 0, 32, 32},
        Rectangle {position->x, position->y, 32 * scale, 32 * scale},
        Vector2 {0, 0},
        0,
        WHITE)
    ;
    // clang-format on
}
