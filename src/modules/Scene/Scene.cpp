#include "Scene.hpp"
#include <raylib-cpp.hpp>
#include <iostream>

Scene::Scene() {
    Ball ball1 = Ball(
        (Vector2){650, 400},
        (Vector2){1, 0},
        3, 50, RED
    );
    balls.push_back(ball1);

    Ball ball2 = Ball(
        (Vector2){(float)850, 400},
        (Vector2){1, 0},
        2, 50, BLUE
    );
    balls.push_back(ball2);
}

Scene::~Scene() {}

void Scene::isMousePressed() {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        Vector2 mousePos = GetMousePosition();
        std::cout << mousePos.x << " " << mousePos.y << std::endl;
        balls.push_back(Ball(mousePos));
    }
}

void Scene::Update() {
    this->isMousePressed();
    Vector2 D = {0};
    float d = 0.0;
    for(ball = balls.begin(); ball != balls.end(); ball++) {
        for(ball2 = balls.begin(); ball2 != balls.end(); ball2++) {
            
            if (ball != ball2) {
                D.x = ball->position.x - ball2->position.x;
                D.y = ball->position.y - ball2->position.y;
                d = sqrtf(D.x * D.x + D.y * D.y);
                if (d == 0) d = 0.000001;
                float sinus = D.x / d;
                float cosinus = D.y / d;
                if (d < ball->radius + ball2->radius){



                    float Vn1 = ball2->direction.x * sinus + ball2->direction.y * cosinus;
                    float Vn2 = ball->direction.x * sinus + ball->direction.y * cosinus;
                    TraceLog(LOG_DEBUG, "Vn1: ", Vn1);
                    TraceLog(LOG_DEBUG, "Vn2: ", Vn2);
                    return;


                    float dt = (ball2->radius + ball->radius - d) / (Vn1 - Vn2);
                    if (dt > 0.6) dt = 0.6;
      		        if (dt < -0.6) dt = -0.6;
      		        ball->position.x -= ball->direction.x * dt;
                    ball->position.y -= ball->direction.y * dt;
                    ball2->position.x -= ball2->direction.x * dt;
                    ball2->position.y -= ball2->direction.y * dt;
                    D.x = ball->position.x - ball2->position.x;
      		        D.y = ball->position.y - ball2->position.y;
                    d = sqrtf(D.x * D.x + D.y * D.y);
                    if (d == 0) d = 0.000001;
                    sinus = D.x/d;
                    cosinus = D.y/d;
                    Vn1 = ball2->direction.x * sinus + ball2->direction.y * cosinus;
                    Vn2 = ball->direction.x * sinus + ball->direction.y *cosinus;
                    float Vt1 = -ball2->direction.x * cosinus + ball2->direction.y * sinus;
      		        float Vt2 = -ball->direction.x * cosinus + ball->direction.y * sinus;
                    float o = Vn2;
                    Vn2 = Vn1;
                    Vn1 = o;

                    ball->direction.x = Vn2 * sinus - Vt2 * cosinus;
                    ball->direction.y = Vn2 * cosinus + Vt2 * sinus;
                    ball2->direction.x = Vn1 * sinus - Vt1 * cosinus;
                    ball2->direction.y = Vn1 * cosinus + Vt1 * sinus;

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