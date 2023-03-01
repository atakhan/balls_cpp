#include "../Ball/Ball.hpp"
#include "../Vector2D/Vector2D.hpp"

#include <raylib-cpp.hpp>
#include <vector>
#include <algorithm>
#include <string>

struct CompareByX
{
    inline bool operator() (const Ball &a, const Ball &b)
    {
        return (a.pos.x < b.pos.x);
    }
};
class Scene {
public:
    std::vector<Ball> balls;

    Scene();
    ~Scene();
    Scene(Scene&&) noexcept;
    Scene& operator=(Scene &&other);
    void Swap(Scene& right);

    void Draw();
    void Update();
    void AddBallToScene();
    void MoveBallByMouse();

private:
    Ball *pSelectedBall = nullptr;
};
