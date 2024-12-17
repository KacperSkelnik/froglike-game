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
    const char*                                            basePath = "../assets/animations";
    std::unordered_map<SpriteDef, std::shared_ptr<Sprite>> sprites  = {};
    const int*                                             frameCount;
    const int                                              framesPerSecond = 10;
    float                                                  spreadsPixels;
    float                                                  scale;

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
    void draw(
        const Sprite*  sprite,
        const int*     frameCount,
        const Vector2* position
    ) const;

  public:
    Animation(
        const int* frameCount,
        float      spreadsPixels,
        float      scale
    );
    void animate(
        SpriteDef      sprite,
        const Vector2* position
    );
};

#endif // ANIMATION_H
