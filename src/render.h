#ifndef RENDER_H
#define RENDER_H
#include "Bullet/Bullet.h"
#include <raylib-cpp.hpp>

#define SPAWN_TIME 60
#define MAX_ENEMY_AMOUNT 10

class Enemy
{
public:
  int radius;
  Vector2 pos;
  Vector2 vel;
  Color color;
  int speed;

  Enemy();

  int randomWall();
  int randomPos(int a);

  void move(Vector2 pPos);
  void update(Vector2 pPos);
  void draw();

  static void spawn(std::vector<Enemy> &enemies, int *tick) {
    if (*tick == SPAWN_TIME && enemies.size() <= MAX_ENEMY_AMOUNT) {
      enemies.push_back(Enemy());
      *tick = 0;
    }
  }

  static void DrawAll(std::vector<Enemy> &enemies) {
    for(auto enemy = enemies.begin(); enemy!=enemies.end(); enemy++)
      enemy->draw();
  }

};

#endif  // RENDER_H