//
// Created by Kacper Skelnik on 13.12.2024.
//

#include "animation.h"

#include <filesystem>
#include <regex>
namespace fs = std::filesystem;

Animation::Animation(
    const int*  frameCount,
    const float desireWidth,
    const float desireHeight
):
    frameCount(frameCount),
    desireWidth(desireWidth),
    desireHeight(desireHeight) {}

int Animation::findNumberOfFrames(
    const char* directory,
    const char* file
) const {
    int  count = 0;
    char folder[256];
    snprintf(folder, 256, "%s/%s", basePath, directory);

    if (!fs::exists(folder) || !fs::is_directory(folder)) {
        return count;
    }

    const std::string filePattern = file + std::string("_\\d.png");
    const std::regex  pattern(filePattern);

    for (const auto& entry : fs::directory_iterator(folder)) {
        if (entry.is_regular_file()) {
            const std::string filename = entry.path().filename().string();
            if (std::regex_match(filename, pattern)) {
                count++;
            }
        }
    }

    return count;
}

Sprite Animation::loadSpriteUnsafe(
    const char* directory,
    const char* file,
    const int   framesNumber
) const {
    Sprite sprite          = Sprite();
    sprite.framesNumber    = framesNumber;
    sprite.framesPerSecond = framesPerSecond;

    auto* images   = static_cast<Image*>(malloc(sizeof(Image) * framesNumber));
    auto* textures = static_cast<Texture2D*>(malloc(sizeof(Texture2D) * framesNumber));

    for (int i = 0; i < framesNumber; i++) {
        char fullPath[256];
        snprintf(fullPath, 256, "%s/%s/%s_%d.png", basePath, directory, file, i);
        images[i]   = LoadImage(fullPath);
        textures[i] = LoadTextureFromImage(images[i]);
    }

    sprite.images   = images;
    sprite.textures = textures;

    return sprite;
}

std::optional<Sprite> Animation::loadSprite(
    const char* directory,
    const char* file
) const {
    int framesNumber = findNumberOfFrames(directory, file);
    if (framesNumber > 0) return loadSpriteUnsafe(directory, file, framesNumber);
    return std::nullopt;
}

void Animation::draw(
    const Sprite*  sprite,
    const int*     frameCount,
    const Vector2* position
) const {
    int frame_number = *frameCount % (sprite->framesNumber * sprite->framesPerSecond) / sprite->framesPerSecond;
    if (frame_number >= sprite->framesNumber) {
        frame_number = 0;
    }

    const auto width  = static_cast<float>(sprite->textures[frame_number].width);
    const auto height = static_cast<float>(sprite->textures[frame_number].height);
    // clang-format off
    DrawTexturePro(
        sprite->textures[frame_number],
        Rectangle {
            0,
            0,
            width,
            height
        },
        Rectangle {
            position->x,
            position->y,
            desireWidth,
            desireHeight
        },
        Vector2 {0, 0},
        0,
        WHITE)
    ;
    // clang-format on
}

void Animation::animate(
    SpriteDef      sprite,
    const Vector2* position
) {
    if (this->sprites.contains(sprite)) {
        const std::shared_ptr<Sprite> loaded = this->sprites[sprite];
        draw(loaded.get(), frameCount, position);
    } else {
        Sprite                loaded;
        std::optional<Sprite> maybeLoaded = loadSprite(sprite.directory, sprite.file);
        if (maybeLoaded.has_value()) loaded = maybeLoaded.value();
        else {
            std::cout << "Cannot load: " << sprite.directory << "/" << sprite.file << std::endl;
            loaded = loadSpriteUnsafe("error", "error", 1);
        }
        std::shared_ptr<Sprite> pointer = std::make_shared<Sprite>(loaded);
        this->sprites.emplace(sprite, pointer);
        draw(pointer.get(), frameCount, position);
    }
}
