//
// Created by Kacper Skelnik on 23.12.2024.
//

#ifndef MAP_H
#define MAP_H
#include "raylib.h"
#include <tmxlite/Map.hpp>

class TileMap {
  private:
    tmx::Map   map;
    Texture2D* textures;
    float      scaleX;
    float      scaleY;

    void drawTile(
        const Texture2D& texture,
        unsigned         tileID,
        unsigned         posX,
        unsigned         posY,
        unsigned         tileWidth,
        unsigned         tileHeight
    ) const;

  public:
    explicit TileMap(
        unsigned    screenWidth,
        unsigned    screenHeight,
        const char* path
    );
    void draw() const;
};

#endif // MAP_H
