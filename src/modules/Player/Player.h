#ifndef PLAYER_H
#define PLAYER_H

#include "../Bullet/Bullet.h"
#include <raylib-cpp.hpp>

class Player
{
public:
  int radius;
  Vector2 pos;
  Vector2 rifle;
  Color color;
  std::vector<Bullet> bullets;
  int speed;

  Player();

  void move();
  
  void rifleUpdate();
  void shoot();
  
  void update();
  void draw();

};

#endif  // PLAYER_H