#include <raylib-cpp.hpp>

#include "modules/Player/Player.h"
#include "modules/Bullet/Bullet.h"
#include "modules/Enemy/Enemy.h"
#include "modules/Collider/Collider.h"

#include <iostream>
#include <vector>
#include <iterator>

struct Game {
  Player player;
  Enemy enemy;
  std::vector<Enemy> enemies;
  int tick;
  int killed;
  int spawnTime;
  bool isOver;
  Texture2D game_bg;

  Game() : enemies() {
    player = Player();
    tick = 1;
    killed = 0;
    isOver = false;
    spawnTime = 60;
    game_bg = LoadTexture("assets/background.png");
  }

  void Restart() {
    tick = 1;
    killed = 0;
    isOver = false;
    spawnTime = 60;
    enemies = std::vector<Enemy>();
    player.reloadPosition();
  }

  void DrawStats() {
    DrawFPS(10,10);
    
    // enemies count
    std::string ec = std::to_string(enemies.size());
    raylib::DrawText(ec, 300, 10, 16, DARKGREEN);

    // killed enemies count
    std::string kec = std::to_string(killed);
    raylib::DrawText(kec, 400, 10, 16, DARKGREEN);
  }

  void DrawGameOver() {
    raylib::Text gameover = raylib::Text("GAME OVER", 64); 
    int width = gameover.Measure();
    raylib::DrawText(
      "GAME OVER", 
      GetScreenWidth() / 2 - (width / 2), 
      GetScreenHeight() / 2 - 64, 
      64, RED
    );

    // FINAL SCORE
    raylib::Text final_score_text = raylib::Text("KILLED: " + std::to_string(killed), 32);
    width = final_score_text.Measure();
    raylib::DrawText(
      "KILLED: " + std::to_string(killed), 
      GetScreenWidth() / 2 - (width / 2), 
      GetScreenHeight() / 2, 
      32, WHITE
    );
  }

  void Draw() {
    if (!isOver) {
      DrawTexture(game_bg, 0,0, WHITE);
      DrawStats();
      player.Draw();
      Enemy::DrawAll(enemies);
      Bullet::DrawAll(player.bullets);
    } else {
      ClearBackground(BLACK);
      DrawGameOver();
    }
  }

  void Update() {
    if (!isOver) {
      player.Update(killed);
      enemy.spawn(enemies, &tick, killed, &spawnTime);
      Collider<Player>::Update(player, enemies, &isOver, &killed);
    } else {
      if (IsKeyPressed(KEY_SPACE)) {
        Restart();
      }
    }
  }

};

int main() {
  int screenWidth = 1024;
  int screenHeight = 1024;

  raylib::Color textColor(LIGHTGRAY);
  raylib::Window window(screenWidth, screenHeight, "Zombie Balls");
  
  SetTargetFPS(60);

  Game game = Game();

  while (!window.ShouldClose()) {
      
      game.Update();

      BeginDrawing();
        ClearBackground(RAYWHITE);
        game.Draw();
      EndDrawing();
      
      game.tick++;
  }

  return 0;
}
