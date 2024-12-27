//
// Created by Kacper Skelnik on 23.12.2024.
//

#include "tilemap.h"

#include "raylib.h"
#include <iostream>
#include <tmxlite/TileLayer.hpp>

TileMap::TileMap(const char* path) {
    if (map.load(path)) {
        const std::vector<tmx::Tileset>& tileSets = map.getTilesets();
        assert(!tileSets.empty());
        auto* _textures = static_cast<Texture2D*>(malloc(sizeof(Texture2D) * tileSets.size()));
        for (std::size_t i = 0; i < tileSets.size(); ++i) {
            const char* _path = tileSets[i].getImagePath().c_str();
            _textures[i]      = LoadTexture(_path);
        }
        textures = _textures;
    }
}

void TileMap::drawTile(
    const Texture2D& texture,
    int              tileID,
    int              posX,
    int              posY,
    int              tileWidth,
    int              tileHeight
) {
    // Calculate the position of the tile in the tileset texture based on its tile ID
    const int tileX = ((tileID - 1) % (texture.width / tileWidth)) * tileWidth;
    const int tileY = ((tileID - 1) / (texture.width / tileWidth)) * tileHeight;

    const Rectangle sourceRect = {(float) tileX, (float) tileY, (float) tileWidth, (float) tileHeight};
    const Rectangle destRect   = {(float) posX, (float) posY, (float) tileWidth, (float) tileHeight};
    DrawTexturePro(texture, sourceRect, destRect, Vector2 {0, 0}, 0, WHITE);
}

void TileMap::draw() const {
    const tmx::Vector2u              tileSize = map.getTileSize();
    const std::vector<tmx::Tileset>& tileSets = map.getTilesets();

    const unsigned width  = map.getTileCount().x;
    const unsigned height = map.getTileCount().y;

    // Render tile layers
    for (const auto& layer : map.getLayers()) {
        if (layer->getType() == tmx::Layer::Type::Tile) {
            const auto& tileLayer = layer->getLayerAs<tmx::TileLayer>();
            const auto& tiles     = tileLayer.getTiles();

            // Iterate through the tiles within the layer's dimensions
            for (unsigned y = 0; y < height; y++) {
                for (unsigned x = 0; x < width; x++) {
                    const tmx::TileLayer::Tile& tile         = tiles[(y * width) + x];
                    unsigned                    offset       = 0;
                    unsigned                    textureIndex = 0;
                    for (unsigned i = 0; i < tileSets.size(); i++) {
                        if (tile.ID >= tileSets[i].getFirstGID() && tile.ID <= tileSets[i].getLastGID()) {
                            offset       = tileSets[i].getFirstGID() - 1;
                            textureIndex = i;
                        }
                    }
                    if (tile.ID != 0) {
                        // Calculate the position of the tile on the screen
                        const unsigned tileX = x * tileSize.x;
                        const unsigned tileY = y * tileSize.y;
                        // Draw the tile at the calculated position
                        drawTile(textures[textureIndex], tile.ID - offset, tileX, tileY, tileSize.x, tileSize.y);
                    }
                }
            }
        }
    }
}