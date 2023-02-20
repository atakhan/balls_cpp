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
        ball->Update();
    }
}

void Scene::Draw() {
    for(ball = balls.begin(); ball != balls.end(); ball++) {
        ball->Draw();
    }
}