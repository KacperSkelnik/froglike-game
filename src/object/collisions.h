//
// Created by Kacper Skelnik on 05.01.2025.
//

#ifndef COLLISIONS_H
#define COLLISIONS_H
#include "../environment/tilemap.h"
#include <optional>

typedef struct CollisionsRegister {
    bool                 leftWall;
    bool                 rightWall;
    bool                 ground;
    bool                 ceiling;
    std::optional<float> overlaps;
    std::optional<float> groundY;
    std::optional<float> ceilingY;

    void reset() {
        this->leftWall  = false;
        this->rightWall = false;
        this->ground    = false;
        this->ceiling   = false;
        this->overlaps  = std::nullopt;
        this->groundY   = std::nullopt;
        this->ceilingY  = std::nullopt;
    }
} CollisionsRegister;

class Collisions {
  private:
    TileMap*           tileMap;
    CollisionsRegister collisionsRegister;

    void detectGround(
        Rectangle rectangle,
        Rectangle referenceRect,
        float     overlaps
    );
    void detectCeiling(
        Rectangle rectangle,
        Rectangle referenceRect,
        float     overlaps
    );
    void detectWalls(
        Rectangle rectangle,
        Rectangle referenceRect,
        float     overlaps
    );
    static bool checkCollisions(
        Rectangle rec1,
        Rectangle rec2
    );

  public:
    explicit Collisions(TileMap* tileMap);
    void                             detect(Rectangle referenceRect);
    [[nodiscard]] CollisionsRegister getRegister() const;
};

#endif // COLLISIONS_H
