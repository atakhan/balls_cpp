#include "../Ball/Ball.hpp"
#include <raylib-cpp.hpp>
#include <list>

class Scene {
public:
    std::list<Ball> balls;
    std::list<Ball>::iterator ball;
    std::list<Ball>::iterator ball2;

    Scene();
    ~Scene();

    void Draw();
    void Update();

    void isMousePressed();

};
