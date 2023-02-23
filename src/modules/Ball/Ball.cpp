#include "Ball.hpp"
#include <raylib-cpp.hpp>
#include <iostream>
#include <string>

Ball::Ball() {
    Init();
}

Ball::Ball(Vector2 pos) {
    Init(pos);
}

Ball::Ball(Vector2 pos, Vector2 vel, Vector2 acc, float radius, Color color) {
    this->pos.x = pos.x;
    this->pos.y = pos.y;
    this->vel.x = vel.x;
    this->vel.y = vel.y;
    this->acc.x = acc.x;
    this->acc.y = acc.y;
    this->radius = radius;
    this->mass = radius * 10.0f;
    this->color = color;
}

Ball::~Ball() {}

void Ball::Init() {
    this->pos.x = GetScreenWidth()/2;
    this->pos.y = GetScreenHeight()/2;
    this->vel.x = 0.0f;
    this->vel.y = 0.0f;
    this->acc.x = 0.0f;
    this->acc.y = 0.0f;
    this->radius = 60.0f;
    this->mass = 600.0f;
    this->color = RED;
}

void Ball::Init(Vector2 pos) {
    this->Init();
    this->pos.x = pos.x;
    this->pos.y = pos.y;
}

void Ball::Draw() {
    DrawCircle(pos.x, pos.y, radius, color);
    // std::string px_str = std::to_string(pos.x);
    // std::string py_str = std::to_string(pos.y);
    // std::string vx_str = std::to_string(vel.x);
    // std::string vy_str = std::to_string(vel.y);
    // raylib::DrawText(px_str + " " + py_str, pos.x, pos.y, 12, BLACK);
    // raylib::DrawText(vx_str + " " + vy_str, pos.x, pos.y + 18, 12, BLACK);
}

void Ball::Update() {
    this->Move();
    this->WallCollider();
}

void Ball::Move() {
    pos.x += vel.x;
    pos.y += vel.y;
}

void Ball::WallCollider() {
    if ((pos.x + radius > GetScreenWidth()) || (pos.x - radius < 0)){
        vel.x *= -1.0f;
    }
    if ((pos.y + radius > GetScreenHeight()) || (pos.y - radius < 0)){
        vel.y *= -1.0f;
    }
}

bool Ball::DoBallsOverlap(Ball ball) {
    return fabs(
        (pos.x - ball.pos.x) * (pos.x - ball.pos.x) + 
        (pos.y - ball.pos.y) * (pos.y - ball.pos.y) 
    ) <= (
        (radius + ball.radius) * (radius + ball.radius)
    );
}

bool Ball::IsPointInBall(Vector2 mousePos) {
    return fabs(
        (pos.x - mousePos.x) * (pos.x - mousePos.x) + 
        (pos.y - mousePos.y) * (pos.y - mousePos.y) 
    ) < (
        (radius * radius)
    );
}


void Ball::DynamicCollider(Ball ball, std::vector<std::pair<Ball*, Ball*>> &vecCollidingPairs) {
    if ((pos.x != ball.pos.x) && (pos.y != ball.pos.y)) {
        if (this->DoBallsOverlap(ball)) {
            // Collision has occured
            vecCollidingPairs.push_back({&*this, &ball});
            // Distance between ball centers
            float fDistance = sqrtf(
                (pos.x - ball.pos.x) * 
                (pos.x - ball.pos.x) + 
                (pos.y - ball.pos.y) * 
                (pos.y - ball.pos.y)
            );
            float fOverlap = 0.5f * (fDistance - radius - ball.radius);
            // Displace current ball
            pos.x -= fOverlap * (pos.x - ball.pos.x) / fDistance;
            pos.y -= fOverlap * (pos.y - ball.pos.y) / fDistance;
            // Displace target ball
            ball.pos.x += fOverlap * (pos.x - ball.pos.x) / fDistance;
            ball.pos.y += fOverlap * (pos.y - ball.pos.y) / fDistance;
        }
    }
}


// bool Ball::isZero(float x) {
//   if (fabs(x) < FLT_MIN) return true;
//   return false;
// }

// float Ball::GetDistanceFrom(const Ball other) {
//     float x = this->position.x - other.position.x;
//     float y = this->position.y - other.position.y;
//     float distance = sqrtf(x * x + y * y);
//     if (distance == 0) 
//         distance = 0.000001;
//     return distance;
// }