#ifndef BALL_H_
#define BALL_H_

#include "../../structs.hpp"
#include <raylib-cpp.hpp>
#include <float.h>
#include <list>
#include <iostream>
#include <string>

class Ball {
public:
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
    void StaticCollider(Ball, std::list<collideLine>&);
    void DynamicCollider(Ball);
    bool isZero(float);
    float GetDistanceFrom(const Ball);
};

#endif  // BALL_H_