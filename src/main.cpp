#include <raylib-cpp.hpp>

#include "modules/Player/Player.h"
#include "modules/Bullet/Bullet.h"
#include "modules/Enemy/Enemy.h"

#include <iostream>
#include <vector>
#include <iterator>

#define SPAWN_TIME 60
#define MAX_ENEMY_AMOUNT 10

bool BulletEnemyCollider(Bullet &bullet, Enemy &enemy) {
  return fabs(
    (bullet.pos.x - enemy.pos.x) * (bullet.pos.x - enemy.pos.x) + 
    (bullet.pos.y - enemy.pos.y) * (bullet.pos.y - enemy.pos.y) 
  ) <= (
    (bullet.radius + enemy.radius) * (bullet.radius + enemy.radius)
  );
}

bool PlayerEnemyCollider(Player &player, Enemy &enemy) {
  return fabs(
    (player.pos.x - enemy.pos.x) * (player.pos.x - enemy.pos.x) + 
    (player.pos.y - enemy.pos.y) * (player.pos.y - enemy.pos.y) 
  ) <= (
    (player.radius + enemy.radius) * (player.radius + enemy.radius)
  );
}

void DrawBulletsCount(Player player) {
  std::string bc = std::to_string(player.bullets.size());
  raylib::DrawText(bc, 100, 10, 16, DARKGREEN);
}

void DrawTicks(int tick) {
  std::string bc = std::to_string(tick);
  raylib::DrawText(bc, 200, 10, 16, BLACK);
}

void DrawEnemiesCount(int count) {
  std::string bc = std::to_string(count);
  raylib::DrawText(bc, 300, 10, 16, DARKGREEN);
}

int main() {
  int screenWidth = 1200;
  int screenHeight = 800;

  raylib::Color textColor(LIGHTGRAY);
  raylib::Window window(screenWidth, screenHeight, "Physic Balls");
  
  SetTargetFPS(60);

  Player player = Player();
  std::vector<Enemy> enemies;

  int ticks = 1;

  bool game = true;

  while (!window.ShouldClose()) {
      if (game) {
        player.update();

        if (ticks == SPAWN_TIME && enemies.size() <= MAX_ENEMY_AMOUNT) {
          enemies.push_back(Enemy());
          ticks = 0;
        }
        
        for(auto enemy = enemies.begin(); enemy!=enemies.end(); enemy++) {
          enemy->update(player.pos);
          if (PlayerEnemyCollider(player, *enemy)) {
            game = false;
          }
        }

        for(auto bullet = player.bullets.begin(); bullet!=player.bullets.end();) {
          bullet->update();
          
          bool isBulletCollideWithEnemy = false;
          for(auto enemy = enemies.begin(); enemy!=enemies.end();) {
            if (BulletEnemyCollider(*bullet, *enemy)) {
              enemy = enemies.erase(enemy);
              isBulletCollideWithEnemy = true;
            } else {
              enemy++;
            }
          }
          
          if (bullet->WallCollider() || isBulletCollideWithEnemy)
            bullet = player.bullets.erase(bullet);
          
          else
            bullet++;
        }
      }

      BeginDrawing();
        ClearBackground(RAYWHITE);
        if (game) {
          DrawFPS(10,10);
          DrawBulletsCount(player);
          DrawTicks(ticks);
          DrawEnemiesCount(enemies.size());
          
          // Draw player
          player.draw();
          
          // Draw enemy
          for(auto enemy = enemies.begin(); enemy!=enemies.end(); enemy++)
            enemy->draw();

          // Draw bullets
          for(auto bullet = player.bullets.begin(); bullet != player.bullets.end(); bullet++) 
            bullet->draw();
        } else {
          raylib::Text gameover = raylib::Text("GAME OVER"); 
          int width = gameover.Measure();
          raylib::DrawText("GAME OVER", GetScreenWidth() / 2 - width, GetScreenHeight() / 2 - 64, 32, DARKGRAY);
        }

      EndDrawing();
      ticks++;
  }

  return 0;
}
