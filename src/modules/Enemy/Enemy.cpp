#include "Enemy.h"
#include "../Bullet/Bullet.h"
#include <iostream>

Enemy::Enemy() {
  int wall = randomWall();
  radius = 30;
  color = BLUE;
  vel.x = 0;
  vel.y = 0;
  speed = 1;
  switch (wall) {
    case 1:  // top wall
      pos.x = randomPos(GetScreenWidth());
      pos.y = 0 + radius;
      break;
    case 2:  // right wall
      pos.x = GetScreenWidth() - radius;
      pos.y = randomPos(GetScreenHeight());
      break;
    case 3:  // bottom wall
      pos.x = randomPos(GetScreenWidth());
      pos.y = GetScreenHeight() - radius;
      break;
    case 4:  // left wall
      pos.x = 0 + radius;
      pos.y = randomPos(GetScreenHeight());
      break;
    default:
      break;
  }
}

int Enemy::randomWall() {
  return 1 + (std::rand() % 4);
}

int Enemy::randomPos(int max) {
  return radius + (std::rand() % max);
}

void Enemy::move(Vector2 plPos) {
  // rifle = GetMousePosition();
  float dx = plPos.x - pos.x;
  float dy = plPos.y - pos.y;
  
  float angle = atan2f(dy, dx);
  
  float dxx = speed * cosf(angle);
  float dyy = speed * sinf(angle);

  pos.x = pos.x + dxx;
  pos.y = pos.y + dyy;
}

void Enemy::update(Vector2 plPos) {
  move(plPos);
}

void Enemy::draw() {
  DrawCircle(
    pos.x,
    pos.y,
    radius,
    color
  );
}