#include "Scene.hpp"
#include <raylib-cpp.hpp>
#include <iostream>

Scene::Scene() {
}

Scene::~Scene() {}

void Scene::Update() {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        Vector2 mousePos = GetMousePosition();
        std::cout << mousePos.x << " " << mousePos.y << std::endl;
        balls.push_back(Ball(mousePos));
    }
    for(ball = balls.begin(); ball != balls.end(); ball++) {
        for(ball2 = balls.begin(); ball2 != balls.end(); ball2++) {
            if (ball != ball2) {
                float Dx = ball->position.x - ball2->position.x;
                float Dy = ball->position.y - ball2->position.y;
                float d = sqrtf(Dx * Dx + Dy * Dy);
                if (d == 0) d = 0.0001;
                float s = Dx/d;
                float e = Dy/d;
                if (d < ball->radius + ball2->radius){
                    float Vn1 = ball2->direction.x * s + ball2->direction.y * e;
                    float Vn2 = ball->direction.x * s + ball->direction.y *e;
                    float dt = (ball2->radius + ball->radius - d)/(Vn1-Vn2);
                    if (dt > 0.6) dt = 0.6;
      		        if (dt < -0.6) dt = -0.6;
      		        ball->position.x -= ball->direction.x * dt;
                    ball->position.y -= ball->direction.y * dt;
                    ball2->position.x -= ball2->direction.x * dt;
                    ball2->position.y -= ball2->direction.y * dt;
                    Dx = ball->position.x - ball2->position.x;
      		        Dy = ball->position.y - ball2->position.y;
                    d = sqrtf(Dx * Dx + Dy * Dy);
                    if (d == 0) d = 0.01;
                    s = Dx/d;
                    e = Dy/d;
                    Vn1 = ball2->direction.x * s + ball2->direction.y * e;
                    Vn2 = ball->direction.x * s + ball->direction.y *e;
                    float Vt1 = -ball2->direction.x * e + ball2->direction.y * s;
      		        float Vt2 = -ball->direction.x * e + ball->direction.y * s;
                    float o = Vn2;
                    Vn2 = Vn1;
                    Vn1 = o;

                    ball->direction.x = Vn2*s-Vt2*e;
                    ball->direction.y = Vn2*e+Vt2*s;
                    ball2->direction.x = Vn1*s-Vt1*e;
                    ball2->direction.y = Vn1*e+Vt1*s;
                    ball->position.x += ball->direction.x * dt;
                    ball->position.y += ball->direction.y * dt;
                    ball2->position.x += ball2->direction.x * dt;
                    ball2->position.y += ball2->direction.y * dt;
                }
            }
        }
        ball->Update();
    }
}

void Scene::Draw() {
    for(ball = balls.begin(); ball != balls.end(); ball++) {
        ball->Draw();
    }
}