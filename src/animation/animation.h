//
// Created by Kacper Skelnik on 13.12.2024.
//

#ifndef ANIMATION_H
#define ANIMATION_H
#include <optional>
#include <raylib.h>

typedef enum Kind {
    DEATH = 0,
    HURT  = 1,
    IDLE  = 2,
    FALL  = 3,
    JUMP  = 4,
    LAND  = 5,
    TURN  = 6,
} Kind;

typedef enum Side {
    LEFT  = 0,
    RIGHT = 1,
} Side;

typedef struct Sprite {
    int        frames;
    int        frames_per_second;
    Texture2D* textures[];
} Sprite;

class Animation {
  public:
    static Sprite load_sprite(const char* name, Kind kind, int number, std::optional<Side> side);
    static void   animate(const Sprite* sprite, int frameCount, const Vector2* position, float scale);
};

#endif // ANIMATION_H
