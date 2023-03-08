#include "Player.h"
#include "../Bullet/Bullet.h"
#include <iostream>

Player::Player() : bullets() {
  radius = 20;
  pos.x = GetScreenWidth() / 2;
  pos.y = GetScreenHeight() / 2;
  color = PINK;
  rifleStart.x = 1;
  rifleStart.y = 1;
  rifleEnd.x = 1;
  rifleEnd.y = 1;
  speed = 3;
  eyeSize = 2;
  // Texture
  texture = LoadTexture("assets/character.png");
  frameWidth = (float)(texture.width/8);   // Sprite one frame rectangle width
  frameHeight = (float)(texture.height/12);           // Sprite one frame rectangle height
  currentFrame = 0;
  currentLine = 2;
  frameRec = { 0, 0, frameWidth, frameHeight };
  active = false;
  framesCounter = 0;
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
  rifleUpdate();
  shoot();
  if (active) {
    framesCounter++;
    if (framesCounter > 2){
      currentFrame++;
      if (currentFrame >= 8) {
        currentFrame = 0;
        currentLine++;

        if (currentLine >= 12) {
          currentLine = 0;
          active = false;
        }
      }

      framesCounter = 0;
    }
  }

  frameRec.x = frameWidth*currentFrame;
  frameRec.y = frameHeight*currentLine;
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
  DrawBody();
  DrawEyes();
  DrawGun();
  DrawTextureRec(texture, frameRec, pos, WHITE);
}