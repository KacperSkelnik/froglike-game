//
// Created by Kacper Skelnik on 15.12.2024.
//

#ifndef SPRITE_H
#define SPRITE_H
#include "../object/side.h"
#include "../object/status.h"
#include "../object/type.h"
#include <__format/format_functions.h>
#include <iostream>
#include <ostream>
#include <raylib.h>
#include <string>

typedef struct Sprite {
    int        framesNumber;
    int        framesPerSecond;
    Image*     images;
    Texture2D* textures;
} Sprite;

typedef struct SpriteDef {
    char* path;
    int   framesNumber;

    bool operator==(const SpriteDef& other) const {
        return std::strcmp(path, other.path) == 0 && framesNumber == other.framesNumber;
    }
    SpriteDef(
        const int          framesNumber,
        const ObjectType   type,
        const ObjectStatus status,
        const ObjectSide   side
    ): framesNumber(framesNumber) {
        char fullPath[256];
        snprintf(fullPath, 256, "%s/%s/%s_%s", toString(type), toString(status), toString(status), toString(side));
        this->path = strdup(fullPath);
    }
} SpriteDef;

template <> struct std::hash<SpriteDef> {
    std::size_t operator()(const SpriteDef& sprite) const noexcept {
        const size_t h1 = sprite.path ? std::hash<std::string>()(sprite.path) : 0;
        const size_t h2 = std::hash<int>()(sprite.framesNumber);
        return h1 ^ (h2 << 1);
    }
};

#endif // SPRITE_H
