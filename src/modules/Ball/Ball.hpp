#ifndef BALL_H_
#define BALL_H_

#include <raylib-cpp.hpp>
#include <float.h>

class Ball {
public:
    
    Vector2 position;
    Vector2 direction;
    float speed;
    float radius;
    Color color;

    Ball();
    Ball(Vector2);
    ~Ball();

    void Init();
    void Init(Vector2);

    void Draw();
    void Update();
    void Move();
    void WallCollider();
    bool isZero(float);
};

#endif  // BALL_H_