#include "physics2d/Collision.h"
#include "physics2d/Manifold.h"
#include "physics2d/PhysicsMath.h"
#include "physics2d/RigidBody.h"
#include "physics2d/Scene.h"
#include "physics2d/Shape.h"

#include <raylib-cpp.hpp>
#include <iostream>

#define BALLS_COUNT 400
#define GRAVITY 10.0f

Shape *pSelectedBall = nullptr;

void DrawCircleShape(const Shape* shape)
{
  const RigidBody* body = shape->body;
  DrawCircle(
    body->position.x,
    body->position.y,
    shape->radius,
    body->color
  );
}

void DrawObbShape(const Shape* shape)
{
  DrawRectangle(
    shape->body->position.x,
    shape->body->position.y,
    shape->width.x,
    shape->width.y,
    BLUE
  );
}

void DrawShape(const Shape* shape)
{
	switch (shape->type) {
		case circle: DrawCircleShape(shape); break;
		case obb: DrawObbShape(shape); break;
	}
}

void WallCollider(Shape* obj) {
    if ((obj->body->position.x + obj->radius >= GetScreenWidth())) {
        obj->body->velocity.x *= -1.0f;
        obj->body->position.x = GetScreenWidth() - obj->radius;
    } else if (obj->body->position.x - obj->radius < 0) {
        obj->body->velocity.x *= -1.0f;
        obj->body->position.x = obj->radius;
    }
    if (obj->body->position.y + obj->radius >= GetScreenHeight()) {
        obj->body->velocity.y *= -1.0f;
        obj->body->position.y = GetScreenHeight() - obj->radius;
    } else if (obj->body->position.y - obj->radius < 0) {
        obj->body->velocity.y *= -1.0f;
        obj->body->position.y = obj->radius;
    }
}

void AddBallToScene(Scene *scene, Circle &c) {
    if (scene->bodies.size() < BALLS_COUNT ) {
        Vector2 mousePos = GetMousePosition();
        RigidBody* b = new RigidBody(c, Vec2(mousePos.x, mousePos.y), 0.0f);
        b->Dynamic(10.0f);
        b->color = raylib::Color(GetRandomValue(0, 240), GetRandomValue(0, 240), GetRandomValue(0, 250), 255);
        scene->Add(b);
    }
}

bool IsPointInBall(Vector2 mousePos, RigidBody* body) {
    return fabs(
        (body->position.x - mousePos.x) * (body->position.x - mousePos.x) + 
        (body->position.y - mousePos.y) * (body->position.y - mousePos.y) 
    ) < (
        (body->shape->radius * body->shape->radius)
    );
}

void MoveBallByMouse(Scene *scene) {
    Vector2 mousePos = GetMousePosition();
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
        pSelectedBall = nullptr;
        for(RigidBody* temp : scene->bodies) {
          WallCollider(temp->shape);
          if (IsPointInBall(mousePos, temp->shape->body)) {
              pSelectedBall = temp->shape;
              break;
          }
        }
    }
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        if (pSelectedBall != nullptr) {
            pSelectedBall->body->position.x = mousePos.x;
            pSelectedBall->body->position.y = mousePos.y;
        }
    }
    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
        pSelectedBall = nullptr;
    }

    // give an impulse to ball
    if (IsMouseButtonReleased(MOUSE_BUTTON_RIGHT)) {
        if (pSelectedBall != nullptr) {
            pSelectedBall->body->velocity.x = 3 * ((pSelectedBall->body->velocity.x) - (float) mousePos.x);
            pSelectedBall->body->velocity.y = 3 * ((pSelectedBall->body->velocity.y) - (float) mousePos.y);
        }
        pSelectedBall = nullptr;
    }
}

int main() {
  // Initialization
  int screenWidth = 1200;
  int screenHeight = 800;

  raylib::Color textColor(LIGHTGRAY);
  raylib::Window window(screenWidth, screenHeight, "Physic Balls");
  
  SetTargetFPS(60);

  Vec2 gravity(0.0f, GRAVITY);
  Scene scene(gravity, 2, 2);
  scene.CorrectionType = NGS;
  real timeStep = 1.0f / 60.0f;
  
  Circle w3(20);  

  // Main game loop
  while (!window.ShouldClose())
  {
      AddBallToScene(&scene, w3);
      MoveBallByMouse(&scene);
      for(RigidBody* temp : scene.bodies) WallCollider(temp->shape);
      scene.Step(timeStep);

      BeginDrawing();
        DrawFPS(10,10);
        ClearBackground(RAYWHITE);
        for(RigidBody* temp : scene.bodies) DrawShape(temp->shape);
      EndDrawing();
  }

  return 0;
}
