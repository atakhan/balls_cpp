#include "Player.h"
#include "../Bullet/Bullet.h"
#include <iostream>

Player::Player() : bullets() {
  radius = 20;
  pos.x = GetScreenWidth() / 2;
  pos.y = GetScreenHeight() / 2;
  color = PINK;
  rifle.x = 1;
  rifle.y = 1;
  speed = 3;
}

void Player::move() {
  if (IsKeyDown(KEY_A)) {
    if (pos.x - radius > 0) {
      pos.x -= speed;
    }
  }
  if (IsKeyDown(KEY_D)) {
    if (pos.x + radius < GetScreenWidth()) {
      pos.x += speed;
    }
  }
  if (IsKeyDown(KEY_W)) {
    if (pos.y - radius > 0) {
      pos.y -= speed;
    }
  }
  if (IsKeyDown(KEY_S)) {
    if (pos.y + radius < GetScreenHeight()) {
      pos.y += speed;
    }
  }
}

void Player::rifleUpdate() {
  rifle = GetMousePosition();
  float dx = rifle.x - pos.x;
  float dy = rifle.y - pos.y;
  
  float angle = atan2f(dy, dx);
  
  float dxx = radius * cosf(angle);
  float dyy = radius * sinf(angle);

  rifle.x = pos.x + dxx;
  rifle.y = pos.y + dyy;
}

void Player::shoot() {
  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
    float vx = (rifle.x - pos.x);
    float vy = (rifle.y - pos.y);
    bullets.push_back(
      Bullet(pos, (Vector2){vx, vy})
    );
  }
}

void Player::update() {
  move();
  rifleUpdate();
  shoot();
}

void Player::draw() {
  DrawCircle(
    pos.x,
    pos.y,
    radius,
    color
  );
  DrawLineEx(
    (Vector2){pos.x,pos.y}, 
    rifle, 
    2, BLACK
  );
}