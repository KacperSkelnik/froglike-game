#include "environment/tilemap.h"
#include "environment/time.h"
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

    Time    time    = Time(60);
    TileMap tileMap = TileMap(screenWidth, screenHeight, "../assets/tilemap/example.tmx");

    Animation          animation = Animation(&frameCount);
    Hero               hero      = Hero(&animation, &tileMap, heroWidth, heroHeight, screenWidth, screenHeight);
    std::vector<Enemy> enemies   = {};

    // Main game loop
    // Detect window close button or ESC key
    while (!WindowShouldClose()) {
        PollInputEvents(); // Poll input events (SUPPORT_CUSTOM_FRAME_CONTROL)

        frameCount++;
        float deltaTime = time.deltaTime();

        tileMap.draw();

        if (enemies.empty()) {
            enemies.emplace_back(&animation, &tileMap, FROG, frogWidth, frogHeight, screenWidth, screenHeight, &hero.position);
        }

        hero.move();
        for (auto& enemy : enemies) {
            enemy.move();
        }

        BeginDrawing();
        {
            ClearBackground(RAYWHITE);

            hero.draw(&deltaTime);
            for (auto& enemy : enemies) {
                enemy.draw(&deltaTime);
            }
        }
        EndDrawing();

        SwapScreenBuffer();
        frameCount = frameCount % 1000;
    }

    CloseWindow();
    return 0;
}
