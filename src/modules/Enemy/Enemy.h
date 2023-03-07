#ifndef ENEMY_H
#define ENEMY_H

#include "../Bullet/Bullet.h"
#include <raylib-cpp.hpp>

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

};

#endif  // ENEMY_H