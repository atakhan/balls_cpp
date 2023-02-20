#include "../Ball/Ball.hpp"
#include <raylib-cpp.hpp>
#include <list>

class Scene {
public:
    std::list<Ball> balls;
    std::list<Ball>::iterator ball;

    Scene();
    ~Scene();

    void Draw();
    void Update();

};
