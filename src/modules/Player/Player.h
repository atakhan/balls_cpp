#ifndef PLAYER_H
#define PLAYER_H

#include "../Bullet/Bullet.h"
#include <raylib-cpp.hpp>

class Player
{
public:
  int radius;
  Vector2 pos;
  Vector2 rifleStart;
  Vector2 rifleEnd;
  Color color;
  std::vector<Bullet> bullets;
  int speed;
  int eyeSize;
  Texture2D texture;
  float frameWidth;
  float frameHeight;
  int currentFrame;
  int currentLine;
  Rectangle frameRec;
  bool active;
  int framesCounter;

  Player();

  void move();
  
  void rifleUpdate();
  void shoot();
  void reloadPosition();  
  void Update(int killed);

  void DrawBody();
  void DrawEyes();
  void DrawGun();
  void Draw();

};

#endif  // PLAYER_H