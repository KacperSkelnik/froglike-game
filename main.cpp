#include "object/enemy.h"
#include "object/hero.h"
#include "raylib.h"
#include <vector>

int main() {
    constexpr int screenWidth  = 1600;
    constexpr int screenHeight = 900;

    InitWindow(screenWidth, screenHeight, "Frog game");

    Hero               hero    = Hero(screenWidth, screenHeight);
    std::vector<Enemy> enemies = {};

    SetTargetFPS(60);

        // Main game loop
        // Detect window close button or ESC key
        while (!WindowShouldClose()) {
                if (enemies.empty()) {
                    enemies.emplace_back(screenWidth, screenHeight, hero.position);
            }

            hero.move();
                for (auto &enemy: enemies) {
                    enemy.move();
                }

            BeginDrawing();

            ClearBackground(RAYWHITE);

            hero.draw();
                for (auto &enemy: enemies) {
                    enemy.draw();
                }

            EndDrawing();
        }

    CloseWindow();
    return 0;
}
