#include "camera/camera.h"
#include "environment/tilemap.h"
#include "environment/time.h"
#include "object/enemy.h"
#include "object/hero.h"
#include "raylib.h"
#include <vector>

int main() {
    constexpr int screenWidth  = 1280;
    constexpr int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "Froglike game");

    int frameCount = 0;

    Time    time    = Time(60);
    TileMap tileMap = TileMap(3, 3, "../assets/tilemap/example.tmx");

    GameCamera         camera    = GameCamera();
    Animation          animation = Animation(&frameCount);
    Hero               hero      = Hero(&animation, &tileMap, &camera);
    std::vector<Enemy> enemies   = {};

    while (!WindowShouldClose()) {
        PollInputEvents(); // Poll input events (SUPPORT_CUSTOM_FRAME_CONTROL)

        frameCount++;
        float deltaTime = time.deltaTime();

        if (enemies.empty()) {
            // enemies.emplace_back(&animation, &tileMap, FROG, &hero.position);
        }

        // Hero updates
        hero.move();
        hero.applyForces(&deltaTime);
        auto [mapWidth, mapHeight] = tileMap.getDimensions();
        camera.updateCenter(mapWidth, mapHeight);

        // Enemies updates
        for (auto& enemy : enemies) {
            enemy.move();
            enemy.applyForces(&deltaTime);
        }

        BeginDrawing();
        {
            ClearBackground(RAYWHITE);
            tileMap.draw(&camera);

            hero.draw();

            for (auto& enemy : enemies) {
                enemy.draw();
            }
        }
        EndDrawing();

        SwapScreenBuffer();
        frameCount = frameCount % 1000;
    }

    CloseWindow();
    return 0;
}
