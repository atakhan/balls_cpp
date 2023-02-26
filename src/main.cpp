#include "modules/Scene/Scene.hpp"
#include "modules/Ball/Ball.hpp"
#include "modules/Vector2D/Vector2D.hpp"

#include <raylib-cpp.hpp>
#include <iostream>

int main() {
    // Initialization
    int screenWidth = 1600;
    int screenHeight = 1200;

    raylib::Color textColor(LIGHTGRAY);
    raylib::Window window(screenWidth, screenHeight, "Myregree Balls");

    Scene scene = Scene();

    SetTargetFPS(60);
    
    // Main game loop
    while (!window.ShouldClose())
    {
        scene.Update();
        BeginDrawing();
            ClearBackground(RAYWHITE);
            scene.Draw();
        EndDrawing();
    }

    return 0;
}
