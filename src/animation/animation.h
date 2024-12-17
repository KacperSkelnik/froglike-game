//
// Created by Kacper Skelnik on 13.12.2024.
//

#ifndef ANIMATION_H
#define ANIMATION_H
#include "sprite.h"
#include <map>
#include <raylib.h>

class Animation {
  private:
    const int                                              framesPerSecond = 10;
    const char*                                            basePath        = "../assets/animations";
    std::unordered_map<SpriteDef, std::shared_ptr<Sprite>> sprites         = {};

    int findNumberOfFrames(
        const char* directory,
        const char* file
    ) const;
    Sprite loadSpriteUnsafe(
        const char* directory,
        const char* file,
        int         framesNumber
    ) const;
    std::optional<Sprite> loadSprite(
        const char* directory,
        const char* file
    ) const;
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
