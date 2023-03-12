#include "Player.h"
#include "../Bullet/Bullet.h"
#include <iostream>

Player::Player() : 
    bullets(),
    moveTopAnimation("assets/character.png", 12, 8, 8),
    moveBottomAnimation("assets/character.png", 12, 8, 8),
    moveLeftAnimation("assets/character.png", 12, 8, 8),
    moveLeftTopAnimation("assets/character.png", 12, 8, 8),
    moveLeftBottomAnimation("assets/character.png", 12, 8, 8),
    moveRightAnimation("assets/character.png", 12, 8, 8),
    moveRightTopAnimation("assets/character.png", 12, 8, 8),
    moveRightBottomAnimation("assets/character.png", 12, 8, 8),
    idleAnimation("assets/character.png", 12, 8, 8)
{
  radius = 20;
  pos = {(float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2};
  color = PINK;
  rifleStart = {1, 1};
  rifleEnd = {1, 1};
  speed = 3;
  eyeSize = 2;
  // Top
  moveTopAnimation.SetCurrentLine(5);
  moveTopAnimation.SetCurrentFrame(0);
  // Right Top
  moveRightTopAnimation.SetCurrentLine(5);
  moveRightTopAnimation.SetCurrentFrame(1);
  // Right
  moveRightAnimation.SetCurrentLine(5);
  moveRightAnimation.SetCurrentFrame(2);
  // Right Bottom
  moveRightBottomAnimation.SetCurrentLine(5);
  moveRightBottomAnimation.SetCurrentFrame(3);
  // Bottom
  moveBottomAnimation.SetCurrentLine(5);
  moveBottomAnimation.SetCurrentFrame(4);
  // Left Bottom
  moveLeftBottomAnimation.SetCurrentLine(5);
  moveLeftBottomAnimation.SetCurrentFrame(5);
  // Left
  moveLeftAnimation.SetCurrentLine(5);
  moveLeftAnimation.SetCurrentFrame(6);
  // Left Top
  moveLeftTopAnimation.SetCurrentLine(5);
  moveLeftTopAnimation.SetCurrentFrame(7);
  // Idle
  idleAnimation.SetCurrentLine(6);
  idleAnimation.SetCurrentFrame(4);

  activeAnimation = 0;

}

void Player::UpdateAnimation() {
  activeAnimation = 0;
  if (IsKeyDown(KEY_W) && !IsKeyDown(KEY_A) && !IsKeyDown(KEY_D)) {
    moveTopAnimation.PlayAnimation(5, 7);
    activeAnimation = 1;
  }
  if (IsKeyDown(KEY_D) && IsKeyDown(KEY_W)) {
    moveRightTopAnimation.PlayAnimation(5, 7);
    activeAnimation = 2;
  }
  if (IsKeyDown(KEY_D) && !IsKeyDown(KEY_W) && !IsKeyDown(KEY_S)) {
    moveRightAnimation.PlayAnimation(5, 7);
    activeAnimation = 3;
  }
  if (IsKeyDown(KEY_D) && IsKeyDown(KEY_S)) {
    moveRightBottomAnimation.PlayAnimation(5, 7);
    activeAnimation = 4;
  }
  if (IsKeyDown(KEY_S) && !IsKeyDown(KEY_A) && !IsKeyDown(KEY_D)) {
    moveBottomAnimation.PlayAnimation(5, 7);
    activeAnimation = 5;
  }
  if (IsKeyDown(KEY_A) && IsKeyDown(KEY_S)) {
    moveLeftBottomAnimation.PlayAnimation(5, 7);
    activeAnimation = 6;
  }
  if (IsKeyDown(KEY_A) && !IsKeyDown(KEY_W) && !IsKeyDown(KEY_S)) {
    moveLeftAnimation.PlayAnimation(5, 7);
    activeAnimation = 7;
  }
  if (IsKeyDown(KEY_A) && IsKeyDown(KEY_W)) {
    moveLeftTopAnimation.PlayAnimation(5, 7);
    activeAnimation = 8;
  }
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
  rifleStart = GetMousePosition();
  float dx = rifleStart.x - pos.x;
  float dy = rifleStart.y - pos.y;
  
  float angle = atan2f(dy, dx);
  
  float dxx = radius * cosf(angle);
  float dyy = radius * sinf(angle);

  float dxx2 = (radius + 5) * cosf(angle);
  float dyy2 = (radius + 5) * sinf(angle);

  rifleStart.x = pos.x + dxx;
  rifleStart.y = pos.y + dyy;
  
  rifleEnd.x = pos.x + dxx2;
  rifleEnd.y = pos.y + dyy2;
}

void Player::shoot() {
  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
    float vx = (rifleStart.x - pos.x);
    float vy = (rifleStart.y - pos.y);
    bullets.push_back(
      Bullet(pos, (Vector2){vx, vy})
    );
  }
}

void Player::reloadPosition() {
  pos.x = GetScreenWidth() / 2;
  pos.y = GetScreenHeight() / 2;
}

void Player::Update(int killed) {
  eyeSize = 1 + (killed /6);
  move();
  UpdateAnimation();
  rifleUpdate();
  shoot();
  if (activeAnimation == 1) moveTopAnimation.UpdateFrameRec();
  if (activeAnimation == 2) moveRightTopAnimation.UpdateFrameRec();
  if (activeAnimation == 3) moveRightAnimation.UpdateFrameRec();
  if (activeAnimation == 4) moveRightBottomAnimation.UpdateFrameRec();
  if (activeAnimation == 5) moveBottomAnimation.UpdateFrameRec();
  if (activeAnimation == 6) moveLeftBottomAnimation.UpdateFrameRec();
  if (activeAnimation == 7) moveLeftAnimation.UpdateFrameRec();
  if (activeAnimation == 8) moveLeftTopAnimation.UpdateFrameRec();
  if (activeAnimation == 0) idleAnimation.UpdateFrameRec();
}

void Player::DrawBody() {
  DrawCircle(
    pos.x,
    pos.y,
    radius,
    color
  );
}

void Player::DrawEyes() {
  DrawCircle(pos.x - 6, pos.y, eyeSize, WHITE);
  DrawCircle(pos.x + 6, pos.y, eyeSize, WHITE);
  DrawCircle(pos.x - 6, pos.y, 2, BLACK);
  DrawCircle(pos.x + 6, pos.y, 2, BLACK);
}

void Player::DrawGun() {
  DrawLineEx(rifleStart, rifleEnd, 2, BLACK);
}

void Player::Draw() {
  // DrawBody();
  // DrawEyes();
  // DrawGun();
  Vector2 spritePos = {pos.x - radius + 4, pos.y - radius};
  if (activeAnimation == 1) moveTopAnimation.DrawFrame(spritePos);
  if (activeAnimation == 2) moveRightTopAnimation.DrawFrame(spritePos);
  if (activeAnimation == 3) moveRightAnimation.DrawFrame(spritePos);
  if (activeAnimation == 4) moveRightBottomAnimation.DrawFrame(spritePos);
  if (activeAnimation == 5) moveBottomAnimation.DrawFrame(spritePos);
  if (activeAnimation == 6) moveLeftBottomAnimation.DrawFrame(spritePos);
  if (activeAnimation == 7) moveLeftAnimation.DrawFrame(spritePos);
  if (activeAnimation == 8) moveLeftTopAnimation.DrawFrame(spritePos);
  if (activeAnimation == 0) idleAnimation.DrawFrame(spritePos);
}