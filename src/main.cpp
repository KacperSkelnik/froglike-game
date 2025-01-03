#include "environment/tilemap.h"
#include "object/enemy.h"
#include "object/hero.h"
#include "raylib.h"
#include <vector>

int main() {
    constexpr int screenWidth  = 1280;
    constexpr int screenHeight = 720;
    constexpr int heroWidth    = 96;
    constexpr int heroHeight   = 96;
    constexpr int frogWidth    = 80;
    constexpr int frogHeight   = 40;

    InitWindow(screenWidth, screenHeight, "Froglike game");

    int frameCount = 0;

    TileMap tileMap = TileMap(screenWidth, screenHeight, "../assets/tilemap/example.tmx");

    Animation          animation = Animation(&frameCount);
    Hero               hero      = Hero(&animation, &tileMap, heroWidth, heroHeight, screenWidth, screenHeight);
    std::vector<Enemy> enemies   = {};

    SetTargetFPS(60);

    // Main game loop
    // Detect window close button or ESC key
    while (!WindowShouldClose()) {
        frameCount++;

        tileMap.draw();

        if (enemies.empty()) {
            // enemies.emplace_back(&animation, &tileMap, FROG, frogWidth, frogHeight, screenWidth, screenHeight, &hero.position);
        }

        hero.move();
        for (auto& enemy : enemies) {
            enemy.move();
        }

        BeginDrawing();

        DrawText(TextFormat("Frame: %i", frameCount), 10, 10, 20, BLACK);
        ClearBackground(RAYWHITE);

        hero.draw();
        for (auto& enemy : enemies) {
            enemy.draw();
        }

        EndDrawing();

        frameCount = frameCount % 1000;
    }

    CloseWindow();
    return 0;
}
