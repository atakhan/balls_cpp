#ifndef BALL_H_
#define BALL_H_

#include <raylib-cpp.hpp>
#include <float.h>

class Ball {
public:
    
    // Vector2 position;
    // Vector2 acceleration;
    // Vector2 velocity;
    Vector2 pos;
    Vector2 vel;
    Vector2 acc;
    float radius;
    float mass;
    Color color;

    Ball();
    Ball(Vector2);
    Ball(Vector2, Vector2, Vector2, float, Color);
    ~Ball();

    void Init();
    void Init(Vector2);

    void Draw();
    void Update();
    void Move();
    void WallCollider();
    bool DoBallsOverlap(Ball);
    bool IsPointInBall(Vector2);
    void DynamicCollider(Ball, std::vector<std::pair<Ball*, Ball*>>&);
    bool isZero(float);
    float GetDistanceFrom(const Ball);
};

#endif  // BALL_H_