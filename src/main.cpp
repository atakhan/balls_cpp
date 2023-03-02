#include "physics2d/Scene.h"

#include <raylib-cpp.hpp>
#include <iostream>

Vec2 gravity(0.0f, -10.0f);
Scene scene(gravity, 10, 4);


static void AngryBirds(void)
{
  RigidBody* b1 = new RigidBody(OBB(22.0f, 0.8f), Vec2(0, -7.5), 0.0f); 
  b1->Static();
  
  OBB w2(2.0f, 0.6f);
  OBB w3(4.3f, 0.4f);

  RigidBody* b2 = new RigidBody(w2, Vec2(-3.0f, -6.43f), 20 * RAD); 
  b2->Static();
  
  RigidBody* b4 = new RigidBody(w2, Vec2( 3.0f, -6.43f), -20 * RAD); 
  b4->Static();
  
  RigidBody* b3 = new RigidBody(w3, Vec2(0, -6.0f), 0.0f); 
  b3->Static();
  
  scene.Add(b1);
  scene.Add(b2);
  scene.Add(b3);
  scene.Add(b4);
  
  int row = 4, col = 3;
  
  for(int i = 0; i < col; i++) // Columns
  {
    for(int j = 0; j < row; j++) // Rows
    {
      OBB wo(0.2f, 1.2f);

      real x = 1.5f * i;
      real y = 1.4f * j - 5.2f;

      RigidBody* b5 = new RigidBody(wo, Vec2(x - 2.1f, y), 0.0f); 
      b5->Dynamic(1.0f);
      scene.Add(b5);
      
      RigidBody* b6 = new RigidBody(wo, Vec2(x - 1.1f, y), 0.0f); 
      b6->Dynamic(1.0);
      scene.Add(b6);
      
      RigidBody* b7 = new RigidBody(wo, Vec2(x - 1.6f, y + 0.7f), PI * 0.5f); // 90 degrees 
      b7->Dynamic(1.0f);		
      scene.Add(b7);
    }
  }
}

int main() {
    // Initialization
    int screenWidth = 1200;
    int screenHeight = 800;

    raylib::Color textColor(LIGHTGRAY);
    raylib::Window window(screenWidth, screenHeight, "Myregree Balls");
    
    SetTargetFPS(60);
    
    Start();

    // Main game loop
    while (!window.ShouldClose())
    {
        
        BeginDrawing();
            ClearBackground(RAYWHITE);

        EndDrawing();
    }

    return 0;
}
