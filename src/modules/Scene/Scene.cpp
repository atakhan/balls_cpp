#include "Scene.hpp"
#include <raylib-cpp.hpp>
#include <iostream>

Scene::Scene() {
    Ball ball = Ball((Vector2){
        (float)GetScreenWidth()/2, 
        (float)GetScreenHeight()/2});
    balls.push_back(ball);
}

Scene::~Scene() {}

void Scene::AddBallToScene() {
    if (IsKeyPressed(KEY_A)) {
        Vector2 mousePos = GetMousePosition();
        std::cout << mousePos.x << " " << mousePos.y << std::endl;
        balls.push_back(Ball(mousePos));
    }
}

void Scene::MoveBallByMouse() {
    Vector2 mousePos = GetMousePosition();
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
        pSelectedBall = nullptr;
        for(ball = balls.begin(); ball != balls.end(); ball++) {
            if (ball->IsPointInBall(mousePos)) {
                pSelectedBall = &*ball;
                break;
            }
        }
    }
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        if (pSelectedBall != nullptr) {
            pSelectedBall->pos.x = mousePos.x;
            pSelectedBall->pos.y = mousePos.y;
        }
    }
    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
        pSelectedBall = nullptr;
    }

    // give an impulse to ball
    if (IsMouseButtonReleased(MOUSE_BUTTON_RIGHT)) {
        if (pSelectedBall != nullptr) {
            pSelectedBall->vel.x = 0.1f * ((pSelectedBall->pos.x) - (float) mousePos.x);
            pSelectedBall->vel.y = 0.1f * ((pSelectedBall->pos.y) - (float) mousePos.y);
        }
        pSelectedBall = nullptr;
    }
}

void Scene::Update() {
    this->AddBallToScene();
    this->MoveBallByMouse();
    for(ball = balls.begin(); ball != balls.end(); ball++) {
        ball->Update();
    }
    for(ball = balls.begin(); ball != balls.end(); ball++) {
        for(ball2 = balls.begin(); ball2 != balls.end(); ball2++) {
            // ball->StaticCollider(*ball2, collideLines);
            ball->DynamicCollider(*ball2);
        }
    }
    
}

void Scene::Draw() {
    // Draw balls
    for(ball = balls.begin(); ball != balls.end(); ball++) {
        ball->Draw();
    }
    
    // Draw collide lines
    for (auto c : collideLines) {
        DrawLine(c.startx, c.starty, c.endx, c.endy, BLACK);
    }
    collideLines.clear();

    // Draw Cue
    if (pSelectedBall != nullptr) {
        DrawLine(pSelectedBall->pos.x, pSelectedBall->pos.y, GetMousePosition().x, GetMousePosition().y, BLUE);
    }

}