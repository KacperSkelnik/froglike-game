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
    char* directory;
    char* file;

    bool operator==(const SpriteDef& other) const {
        return std::strcmp(directory, other.directory) == 0 && std::strcmp(file, other.file) == 0;
    }
    SpriteDef(
        const int          framesNumber,
        const ObjectType   type,
        const ObjectStatus status,
        const ObjectSide   side
    ) {
        char directoryName[256];
        snprintf(directoryName, 256, "%s/%s", toString(type), toString(status));

        char fileName[256];
        snprintf(fileName, 256, "%s_%s", toString(status), toString(side));

        this->directory = strdup(directoryName);
        this->file      = strdup(fileName);
    }
} SpriteDef;

template <> struct std::hash<SpriteDef> {
    std::size_t operator()(const SpriteDef& sprite) const noexcept {
        const size_t h1 = sprite.directory ? std::hash<std::string>()(sprite.directory) : 0;
        const size_t h2 = sprite.directory ? std::hash<std::string>()(sprite.file) : 0;
        return h1 ^ (h2 << 1);
    }
};

#endif // SPRITE_H
