#include "Ball.hpp"
#include <raylib-cpp.hpp>

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
    int randomRadius = 2 + (std::rand() % 10);
    this->radius = randomRadius;
    this->mass = randomRadius * 10;
    this->color = DARKGREEN;
}

void Ball::Init(Vector2 pos) {
    this->Init();
    this->pos.x = pos.x;
    this->pos.y = pos.y;
}

void Ball::Draw() {
    DrawCircle(pos.x, pos.y, radius, color);
}

void Ball::Update() {
    this->Move();
    // this->WallCollider();
}

void Ball::Move() {
    acc.x = -vel.x * 0.01f;
    acc.y = -vel.y * 0.01f;

    vel.x += acc.x;
    vel.y += acc.y;

    pos.x += vel.x;
    pos.y += vel.y;

    if (fabs(vel.x * vel.x + vel.y * vel.y) < 0.01f) {
        vel.x = 0;
        vel.y = 0;
    }

    if ((pos.x + radius > GetScreenWidth()) || (pos.x - radius < 0)){
        vel.x *= -1.0f;
    }
    if ((pos.y + radius > GetScreenHeight()) || (pos.y - radius < 0)){
        vel.y *= -1.0f;
    }

    // Clamp velocity near zero
    if (fabs(vel.x * vel.x + vel.y * vel.y) < 0.01f)
    {
        vel.x = 0;
        vel.y = 0;
    }
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

void Ball::StaticCollider(Ball ball, std::list<collideLine> &collideLines) {
    if ((pos.x != ball.pos.x) && (pos.y != ball.pos.y)) {
        if (this->DoBallsOverlap(ball)) {
            
            // Collision has occured, add collide line to draw
            collideLines.push_back((collideLine){pos.x, pos.y, ball.pos.x, ball.pos.y});
            
            // Distance between ball centers
            float fDistance = sqrtf(
                (pos.x - ball.pos.x) * 
                (pos.x - ball.pos.x) + 
                (pos.y - ball.pos.y) * 
                (pos.y - ball.pos.y)
            );
            float fOverlap = 0.5f * (fDistance - radius - ball.radius);
            
            // TODO! 
            // Displace current ball
            pos.x -= fOverlap * (pos.x - ball.pos.x) / fDistance;
            pos.y -= fOverlap * (pos.y - ball.pos.y) / fDistance;
            
            // Displace target ball
            ball.pos.x += fOverlap * (pos.x - ball.pos.x) / fDistance;
            ball.pos.y += fOverlap * (pos.y - ball.pos.y) / fDistance;
        }
    }
}

void Ball::DynamicCollider(Ball ball) {
    if ((pos.x != ball.pos.x) && (pos.y != ball.pos.y)) {
        if (this->DoBallsOverlap(ball)) {
            
            // Distance between ball centers
            float fDistance = sqrtf(
                (pos.x - ball.pos.x) * 
                (pos.x - ball.pos.x) + 
                (pos.y - ball.pos.y) * 
                (pos.y - ball.pos.y)
            );
            
            // Normal
            float nx = (ball.pos.x - pos.x) / fDistance;
            float ny = (ball.pos.y - pos.y) / fDistance;

            // Tangent
            float tx = -ny;
            float ty = nx;

            // Dot Product Tangent
            float dpTan1 = vel.x * tx + vel.y * ty;
            float dpTan2 = ball.vel.x * tx + ball.vel.y * ty;

            // Dot Product Normal
            float dpNorm1 = vel.x * nx + vel.y * ny;
            float dpNorm2 = ball.vel.x * nx + ball.vel.y * ny;

            // Conservation of momentum in 1D
            float m1 = (dpNorm1 * (mass - ball.mass) + 2.0f * ball.mass * dpNorm2) / (mass + ball.mass);
            float m2 = (dpNorm2 * (ball.mass - mass) + 2.0f * mass * dpNorm1) / (mass + ball.mass);

            // update ball velocities
            vel.x = tx * dpTan1 + nx * m1;
            vel.y = ty * dpTan1 + ny * m1;
            ball.vel.x = tx * dpTan2 + nx * m2;
            ball.vel.y = ty * dpTan2 + ny * m2;

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