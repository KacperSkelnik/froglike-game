#include "camera/camera.h"
#include "environment/tilemap.h"
#include "environment/time.h"
#include "object/enemy.h"
#include "object/hero.h"
#include "raylib.h"
#include <vector>

int main() {
    constexpr int screenWidth  = 1920;
    constexpr int screenHeight = 1080;

    InitWindow(screenWidth, screenHeight, "Froglike game");

    int frameCount = 0;

    Time    time               = Time(60);
    TileMap tileMap            = TileMap(3, 3, "../assets/tilemap/example.tmx");
    auto [mapWidth, mapHeight] = tileMap.getDimensions();

    GameCamera         camera    = GameCamera();
    Animation          animation = Animation(&frameCount);
    Hero               hero      = Hero(&animation, &tileMap, &camera);
    std::vector<Enemy> enemies   = {};

    while (!WindowShouldClose()) {
        PollInputEvents(); // Poll input events (SUPPORT_CUSTOM_FRAME_CONTROL)

        frameCount++;
        float deltaTime = time.deltaTime();

        if (enemies.empty()) {
            enemies.emplace_back(FROG, &animation, &tileMap, &camera);
        }

        // Hero/Camera update
        hero.move();
        hero.applyForces(&deltaTime);
        hero.updatePosition(mapWidth, mapHeight);

        // Enemies update
        for (auto& enemy : enemies) {
            enemy.move();
            enemy.applyForces(&deltaTime);
            enemy.updatePosition();
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
