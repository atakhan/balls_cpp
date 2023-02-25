#include "../Ball/Ball.hpp"
#include <raylib-cpp.hpp>
#include <list>

class Scene {
public:
    std::list<Ball> balls;
    std::list<Ball>::iterator ball;
    std::list<Ball>::iterator ball2;
    std::list<ball::collideLine> collideLines;

    Scene();
    ~Scene();

    void Draw();
    void Update();

    void AddBallToScene();
    void MoveBallByMouse();
private:
    Ball *pSelectedBall = nullptr;
};
