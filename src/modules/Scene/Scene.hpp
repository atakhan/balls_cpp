#include "../Ball/Ball.hpp"
#include "../Vector2D/Vector2D.hpp"

#include <raylib-cpp.hpp>
#include <list>
#include <string>

class Scene {
public:
    std::vector<Ball> balls;

    Scene();
    ~Scene();

    void Draw();
    void Update();
    void AddBallToScene();
    void MoveBallByMouse();
private:
    Ball *pSelectedBall = nullptr;
};
