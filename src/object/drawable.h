//
// Created by Kacper Skelnik on 07.01.2025.
//

#ifndef DRAWABLE_H
#define DRAWABLE_H
#include "../animation/animation.h"
#include "raylib.h"

class Drawable {
  private:
    Animation* animation;

  protected:
    Vector2           position {};
    float             width;
    float             height;
    virtual SpriteDef getSprite() = 0;

  public:
    virtual ~Drawable() = default;
    explicit Drawable(
        Animation* animation,
        float      width,
        float      height
    );
    [[nodiscard]] Rectangle getRectangle() const;
    void                    draw();
};

#endif // DRAWABLE_H
