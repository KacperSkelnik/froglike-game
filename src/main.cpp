#include "object/enemy.h"
#include "object/hero.h"
#include "raylib.h"
#include <vector>

int main() {
    constexpr int screenWidth  = 1600;
    constexpr int screenHeight = 900;

    InitWindow(screenWidth, screenHeight, "Froglike game");

    int frameCount = 0;

    Animation          animation = Animation();
    Hero               hero      = Hero(&animation, HERO, screenWidth, screenHeight);
    std::vector<Enemy> enemies   = {};

    SetTargetFPS(60);

    // Main game loop
    // Detect window close button or ESC key
    while (!WindowShouldClose()) {
        frameCount++;

        if (enemies.empty()) {
            enemies.emplace_back(&animation, FROG, screenWidth, screenHeight, &hero.position, &frameCount);
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
