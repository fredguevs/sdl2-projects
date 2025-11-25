#ifndef GAME_OBJ_H
#define GAME_OBJ_H

#include "Game.h"

class GameObject
{

public:
  GameObject(const char* textureSheet, int x, int y);
  ~GameObject();

  void Update(float deltaTime);

  void Render();

  float speed = 100.0f;

private:
  /* data */

  int x_pos, y_pos;

  SDL_Texture * texture;
  SDL_Rect srcRect, destRect;

};




#endif // GAME_OBJ_H
