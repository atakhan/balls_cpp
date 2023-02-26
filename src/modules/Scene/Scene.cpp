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
    if (balls.size() < BALLS_COUNT ) {
        Vector2 mousePos = GetMousePosition();
        std::cout << mousePos.x << " " << mousePos.y << std::endl;
        balls.push_back(Ball(mousePos));
    }
}

void Scene::MoveBallByMouse() {
    Vector2 mousePos = GetMousePosition();
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
        pSelectedBall = nullptr;
        for (size_t i = 0; i < balls.size(); ++i) {
            if (balls[i].IsPointInBall(mousePos)) {
                pSelectedBall = &balls[i];
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

    for (size_t i = 0; i < balls.size(); ++i) {
        balls[i].Move();
    }
    for (size_t i = 0; i < balls.size(); ++i) {
        balls[i].WallCollider();
        for (size_t j = 0; j < balls.size(); ++j) {
            if (balls[i].pos.x != balls[j].pos.x || balls[i].pos.y != balls[j].pos.y) {
                if (balls[i].DoBallsOverlap(balls[j])) {
                    balls[i].ResolveCollision(balls[j]);
                    balls[i].WallCollider();
                }

            }
        // for (size_t j = i + 1; j < balls.size(); ++j) {
        }
    }    
}

void Scene::Draw() {
    DrawFPS(10,10);
    std::string ballsCount = std::to_string(balls.size());
    raylib::DrawText(ballsCount, 100, 10, 20, RED);
    // Draw balls
    for (size_t i = 0; i < balls.size(); ++i) {
        balls[i].Draw();
    }
    // Draw Cue
    if (pSelectedBall != nullptr) {
        DrawLine(pSelectedBall->pos.x, pSelectedBall->pos.y, GetMousePosition().x, GetMousePosition().y, BLUE);
    }

}