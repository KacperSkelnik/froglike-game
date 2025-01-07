//
// Created by Kacper Skelnik on 23.12.2024.
//

#include "tilemap.h"

#include "layerType.h"
#include "raylib.h"
#include <iostream>
#include <tmxlite/ImageLayer.hpp>
#include <tmxlite/TileLayer.hpp>

TileMap::TileMap(
    const float scaleX,
    const float scaleY,
    const char* path
):
    scaleX(scaleX),
    scaleY(scaleY) {
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

std::vector<Rectangle> TileMap::getGrounds() const {
    return grounds;
}

void TileMap::drawTile(
    const Texture2D& texture,
    const unsigned   tileID,
    const float      posX,
    const float      posY,
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
        posX,
        posY,
        scaleX * static_cast<float>(tileWidth),
        scaleY * static_cast<float>(tileHeight)
    };
    // clang-format on
    DrawTexturePro(texture, sourceRect, destRect, Vector2 {0, 0}, 0, WHITE);

    if (layerType == GROUND) grounds.push_back(destRect);
}

void TileMap::draw(const GameCamera* camera) {
    grounds.clear();
    const std::vector<tmx::Tileset>& tileSets = map.getTilesets();

    const auto width  = static_cast<float>(map.getTileCount().x);
    const auto height = static_cast<float>(map.getTileCount().y);

    const auto tileWidth  = static_cast<float>(map.getTileSize().x);
    const auto tileHeight = static_cast<float>(map.getTileSize().y);

    const auto screenWidth  = static_cast<float>(GetScreenWidth());
    const auto screenHeight = static_cast<float>(GetScreenHeight());

    // apply only relevant part of the Tilemap
    const float fromY = std::min(height, height + (camera->camera.target.y - camera->camera.offset.y) / tileHeight / scaleY);
    const float toY   = std::max(0.f, fromY - 1 - screenHeight / tileHeight / scaleY);
    const float fromX = std::max(0.f, (camera->camera.target.x - camera->camera.offset.x) / tileWidth / scaleX);
    const float toX   = std::min(width, (camera->camera.target.x + screenWidth) / tileWidth / scaleX);

    for (const auto& layer : map.getLayers()) {
        // Render tile layers
        if (layer->getType() == tmx::Layer::Type::Tile) {
            const auto&     tileLayer = layer->getLayerAs<tmx::TileLayer>();
            const auto&     tiles     = tileLayer.getTiles();
            const LayerType layerType = fromString(tileLayer.getClass());

            // Iterate through the tiles within the layer's dimensions
            for (auto y = static_cast<unsigned>(fromY); y > static_cast<unsigned>(toY); y--) {
                for (auto x = static_cast<unsigned>(fromX); x < static_cast<unsigned>(toX); x++) {
                    const tmx::TileLayer::Tile& tile         = tiles[(y * static_cast<unsigned>(width)) + x];
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
                        const float tileX = scaleX * (static_cast<float>(x) - fromX) * tileWidth;
                        const float tileY = screenHeight - scaleY * (fromY - static_cast<float>(y)) * tileHeight;

                        // Draw the tile at the calculated position
                        drawTile(textures[textureIndex], tile.ID - offset, tileX, tileY, tileWidth, tileHeight, layerType);
                    }
                }
            }
        }
    }
}

Vector2 TileMap::getDimensions() const {
    const auto width      = static_cast<float>(map.getTileCount().x);
    const auto height     = static_cast<float>(map.getTileCount().y);
    const auto tileWidth  = static_cast<float>(map.getTileSize().x);
    const auto tileHeight = static_cast<float>(map.getTileSize().y);

    return {width * tileWidth * scaleX, height * tileHeight * scaleY};
}