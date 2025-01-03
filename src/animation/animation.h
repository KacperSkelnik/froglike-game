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
        const Sprite* sprite,
        const int*    frameCount,
        Rectangle     rectangle
    );

  public:
    explicit Animation(const int* frameCount);
    void animate(
        SpriteDef sprite,
        Rectangle rectangle
    );
};

#endif // ANIMATION_H
