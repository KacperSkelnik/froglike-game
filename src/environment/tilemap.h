//
// Created by Kacper Skelnik on 23.12.2024.
//

#ifndef MAP_H
#define MAP_H
#include "layerType.h"
#include "raylib.h"
#include <tmxlite/Map.hpp>

class TileMap {
  private:
    tmx::Map               map;
    Texture2D*             textures;
    float                  scaleX;
    float                  scaleY;
    std::vector<Rectangle> grounds = {};

    void drawTile(
        const Texture2D& texture,
        unsigned         tileID,
        unsigned         posX,
        unsigned         posY,
        unsigned         tileWidth,
        unsigned         tileHeight,
        LayerType        layerType
    );

  public:
    explicit TileMap(
        unsigned    screenWidth,
        unsigned    screenHeight,
        const char* path
    );
    [[nodiscard]] std::vector<Rectangle> getGrounds() const;
    void                                 draw();
};

#endif // MAP_H
