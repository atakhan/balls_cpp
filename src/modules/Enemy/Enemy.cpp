#include "Enemy.h"
#include "../Bullet/Bullet.h"
#include <iostream>

#define SPEED_UPGRADE 1

Enemy::Enemy() : animation("assets/zombies_v2.png", 17, 1, 17) {
  int wall = randomWall();
  radius = 30;
  color = BLUE;
  vel.x = 0;
  vel.y = 0;
  speed = 1;
  angle = 0.0f;
  animation.SetCurrentLine(0);
  animation.SetCurrentFrame(0);

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
  
  angle = atan2f(dy, dx);
  
  float dxx = speed * cosf(angle);
  float dyy = speed * sinf(angle);

  pos.x = pos.x + dxx;
  pos.y = pos.y + dyy;
}

void Enemy::update(Vector2 plPos) {
  move(plPos);
  animation.PlayAnimation(1, 17);
  animation.UpdateFrameRec();
}

void Enemy::draw() {
  // DrawCircle(
  //   pos.x,
  //   pos.y,
  //   radius,
  //   color
  // );
  Vector2 spritePos = {pos.x, pos.y};
  animation.DrawFramePro(spritePos, angle);
}

void Enemy::spawn(std::vector<Enemy> &enemies, int *tick, int killed, int *spawnTime) {
  // if (*tick == SPAWN_TIME && enemies.size() < MAX_ENEMY_AMOUNT) {
  if (*tick == *spawnTime) {
    Enemy enemy = Enemy();
    (killed == 0)
      ? enemy.speed = 1
      : enemy.speed = 1 + (killed / 4);
    enemies.push_back(enemy);
    if (*spawnTime > 30) {
      *spawnTime -= 1;
    }
    *tick = 0;
  }
}