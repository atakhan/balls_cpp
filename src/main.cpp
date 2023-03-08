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

  Game() : enemies() {
    player = Player();
    tick = 1;
    killed = 0;
    isOver = false;
    spawnTime = 60;
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

    // bullets count
    std::string bc = std::to_string(player.bullets.size());
    raylib::DrawText(bc, 100, 10, 16, DARKGREEN);
    
    // draw ticks
    std::string tc = std::to_string(tick);
    raylib::DrawText(tc, 200, 10, 16, BLACK);
    
    // enemies count
    std::string ec = std::to_string(enemies.size());
    raylib::DrawText(ec, 300, 10, 16, DARKGREEN);

    // killed enemies count
    std::string kec = std::to_string(killed);
    raylib::DrawText(kec, 400, 10, 16, DARKGREEN);
  }

  void DrawGameOver() {
    raylib::Text gameover = raylib::Text("GAME OVER"); 
    int width = gameover.Measure();
    raylib::DrawText(
      "GAME OVER", 
      GetScreenWidth() / 2 - width, 
      GetScreenHeight() / 2 - 64, 
      32, DARKGRAY
    );

    // FINAL SCORE
    raylib::Text final_score_text = std::string("KILLED: " + std::to_string(killed));
    width = final_score_text.Measure();
    raylib::DrawText(
      "KILLED: " + std::to_string(killed), 
      GetScreenWidth() / 2 - width, 
      GetScreenHeight() / 2, 
      32, DARKGRAY
    );
  }

  void Draw() {
    if (!isOver) {
      DrawStats();
      player.Draw();
      Enemy::DrawAll(enemies);
      Bullet::DrawAll(player.bullets);
    } else {
      DrawGameOver();
    }
  }

  void Update() {
    if (!isOver) {
      player.Update(killed);
      enemy.spawn(enemies, &tick, killed, &spawnTime);
      Collider<Player>::Update(player, enemies, &isOver, &killed);
    } else {
      if (IsKeyPressed(KEY_ENTER)) {
        Restart();
      }
    }
  }

};

int main() {
  int screenWidth = 1200;
  int screenHeight = 800;

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
