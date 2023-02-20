#include "Ball.hpp"
#include <raylib-cpp.hpp>
#include <iostream>

Ball::Ball() {
    Init();
}

Ball::Ball(Vector2 pos) {
    Init(pos);
}

Ball::~Ball() {}

void Ball::Init() {
    this->position.x = 200;
    this->position.y = 200;
    this->direction.x = 0.1;
    this->direction.y = 0.1;
    this->speed = 1;
    this->color = RED;
    this->radius = 20;
}

void Ball::Init(Vector2 pos) {
    this->position.x = pos.x;
    this->position.y = pos.y;
    this->direction.x = 0.1;
    this->direction.y = 0.1;
    this->speed = 1;
    this->color = RED;
    this->radius = 20;
}

void Ball::Draw() {
    DrawCircle(position.x, position.y, radius, color);
}

void Ball::Update() {
    this->Move();
    this->WallCollider();
}

void Ball::Move() {
    float vx = direction.x;
    float vy = direction.y;
    if (isZero(vx) && isZero(vy)) {
        this->position.x += vx;
        this->position.y += vy;
    } else if (isZero(vx) && !isZero(vy)) {
        this->position.y += vy * speed;
    } else if (!isZero(vx) && isZero(vy)) {
        this->position.x += vx * speed;
    } else {
        int sign_x = (vx < 0) ? -1 : 1;
        int sign_y = (vy < 0) ? -1 : 1;
        float degAngle = atanf(fabs(vy)/fabs(vx));
        float velocityX = cos(degAngle) * sign_x * speed;
        float velocityY = sin(degAngle) * sign_y * speed;
        position.x += velocityX;
        position.y += velocityY;
    }
}

void Ball::WallCollider() {
    if ((position.x + radius > GetScreenWidth()) || (position.x - radius < 0)){
        direction.x *= -1.0f;
    }
    if ((position.y + radius > GetScreenHeight()) || (position.y - radius < 0)){
        direction.y *= -1.0f;
    }
}

bool Ball::isZero(float x) {
  if (fabs(x) < FLT_MIN) return true;
  return false;
}