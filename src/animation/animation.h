//
// Created by Kacper Skelnik on 13.12.2024.
//

#ifndef ANIMATION_H
#define ANIMATION_H
#include <map>
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
    Image*     images;
    Texture2D* textures;
} Sprite;

typedef struct SpriteDef {
    char*               name;
    Kind                kind;
    int                 number;
    std::optional<Side> side;

    bool operator==(const SpriteDef& other) const {
        return (name == other.name && kind == other.kind && side == other.side);
    }
} SpriteDef;

template <> struct std::hash<SpriteDef> {
    std::size_t operator()(const SpriteDef& sprite) const noexcept {
        const std::size_t h1 = std::hash<std::string>()(sprite.name);
        const std::size_t h2 = std::hash<int>()(static_cast<int>(sprite.kind));
        const std::size_t h3 = std::hash<int>()(sprite.number);
        const std::size_t h4 = sprite.side ? std::hash<int>()(static_cast<int>(*sprite.side)) : 0;

        return h1 ^ (h2 << 1) ^ (h3 << 2) ^ (h4 << 3);
    }
};

class Animation {
  private:
    std::unordered_map<SpriteDef, std::shared_ptr<Sprite>> sprites = {};

    static Sprite load_sprite(
        const char*         name,
        Kind                kind,
        int                 number,
        std::optional<Side> side
    );
    static void draw(
        const Sprite*  sprite,
        const int*     frameCount,
        const Vector2* position,
        float          scale
    );

  public:
    void animate(
        SpriteDef      sprite,
        const int*     frameCount,
        const Vector2* position,
        float          scale
    );
};

#endif // ANIMATION_H
