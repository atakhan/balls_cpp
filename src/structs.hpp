namespace ball {

struct collideLine
{
    float startx;
    float starty;
    float endx;
    float endy;
};

class Vector2D {
public:
    float x;
    float y;

    Vector2D() {
        x = 0.0f;
        y = 0.0f;
    }

    ~Vector2D() {}

    Vector2D sum(Vector2D other) {
        Vector2D result = Vector2D();
        result.x += other.x;
        result.y += other.y;
        return result;
    }

    Vector2D subtract(Vector2D other) {
        Vector2D result = Vector2D();
        result.x -= other.x;
        result.y -= other.y;
        return result;
    }

    Vector2D multiply(double number) {
        Vector2D result = Vector2D();
        result.x *= number;
        result.y *= number;
        return result;
    }

};
} // namespace ball