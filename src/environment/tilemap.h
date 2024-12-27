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

    static void drawTile(
        const Texture2D& texture,
        int              tileID,
        int              posX,
        int              posY,
        int              tileWidth,
        int              tileHeight
    );

  public:
    explicit TileMap(const char* path);
    void draw() const;
};

#endif // MAP_H
