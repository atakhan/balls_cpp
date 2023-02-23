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

void Scene::isRightMouseBtnPressed() {
    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
        Vector2 mousePos = GetMousePosition();
        std::cout << mousePos.x << " " << mousePos.y << std::endl;
        balls.push_back(Ball(mousePos));
    }
}

void Scene::isLeftMouseBtnPressed() {
    Vector2 mousePos = GetMousePosition();
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
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
}

void Scene::Update() {
    this->isRightMouseBtnPressed();
    this->isLeftMouseBtnPressed();
    for(ball = balls.begin(); ball != balls.end(); ball++) {
        for(ball2 = balls.begin(); ball2 != balls.end(); ball2++) {
            ball->DynamicCollider(*ball2, vecCollidingPairs);
        }
        ball->Update();
    }
    
}

void Scene::Draw() {
    for(ball = balls.begin(); ball != balls.end(); ball++) {
        ball->Draw();
    }
    for (auto c : vecCollidingPairs)
        DrawLine(c.first->pos.x, c.first->pos.y, c.second->pos.x, c.second->pos.y, BLACK);
    

}