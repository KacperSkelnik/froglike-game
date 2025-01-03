//
// Created by Kacper Skelnik on 23.12.2024.
//

#include "tilemap.h"

#include "layerType.h"
#include "raylib.h"
#include <iostream>
#include <tmxlite/TileLayer.hpp>

TileMap::TileMap(
    const unsigned screenWidth,
    const unsigned screenHeight,
    const char*    path
) {
    if (map.load(path)) {
        const std::vector<tmx::Tileset>& tileSets = map.getTilesets();
        assert(!tileSets.empty());
        auto* _textures = static_cast<Texture2D*>(malloc(sizeof(Texture2D) * tileSets.size()));
        for (std::size_t i = 0; i < tileSets.size(); ++i) {
            const char* _path = tileSets[i].getImagePath().c_str();
            _textures[i]      = LoadTexture(_path);
        }
        textures = _textures;
        scaleX   = static_cast<float>(screenWidth) / static_cast<float>(map.getTileCount().x * map.getTileSize().x);
        scaleY   = static_cast<float>(screenHeight) / static_cast<float>(map.getTileCount().y * map.getTileSize().y);
    }
}

std::vector<Rectangle> TileMap::getGrounds() const {
    return grounds;
}

void TileMap::drawTile(
    const Texture2D& texture,
    const unsigned   tileID,
    const unsigned   posX,
    const unsigned   posY,
    const unsigned   tileWidth,
    const unsigned   tileHeight,
    const LayerType  layerType
) {
    // Calculate the position of the tile in the tileset texture based on its tile ID
    const unsigned tileX = ((tileID - 1) % (texture.width / tileWidth)) * tileWidth;
    const unsigned tileY = ((tileID - 1) / (texture.width / tileWidth)) * tileHeight;

    // clang-format off
    const Rectangle sourceRect = {
        static_cast<float>(tileX),
        static_cast<float>(tileY),
        static_cast<float>(tileWidth),
        static_cast<float>(tileHeight)
    };
    const Rectangle destRect = {
        static_cast<float>(posX),
        static_cast<float>(posY),
        scaleX * static_cast<float>(tileWidth),
        scaleY * static_cast<float>(tileHeight)
    };
    // clang-format on
    DrawTexturePro(texture, sourceRect, destRect, Vector2 {0, 0}, 0, WHITE);

    if (layerType == GROUND) grounds.push_back(destRect);
}

void TileMap::draw() {
    const tmx::Vector2u              tileSize = map.getTileSize();
    const std::vector<tmx::Tileset>& tileSets = map.getTilesets();

    const unsigned width  = map.getTileCount().x;
    const unsigned height = map.getTileCount().y;

    // Render tile layers
    for (const auto& layer : map.getLayers()) {
        if (layer->getType() == tmx::Layer::Type::Tile) {
            const auto&     tileLayer = layer->getLayerAs<tmx::TileLayer>();
            const auto&     tiles     = tileLayer.getTiles();
            const LayerType layerType = fromString(tileLayer.getClass());

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
                        const auto tileX = static_cast<unsigned>(floor(scaleX * static_cast<float>(x * tileSize.x)));
                        const auto tileY = static_cast<unsigned>(floor(scaleY * static_cast<float>(y * tileSize.y)));
                        // Draw the tile at the calculated position
                        drawTile(textures[textureIndex], tile.ID - offset, tileX, tileY, tileSize.x, tileSize.y, layerType);
                    }
                }
            }
        }
    }
}