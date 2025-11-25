#ifndef MAP_H
#define MAP_H
#include "Game.h"

class Map
{
public:
  Map();
  ~Map();

  void LoadMap(int map[20][25]);
  void DrawMap();

private:

  SDL_Rect src, dst;
  SDL_Texture* dirt;
  SDL_Texture* grass;
  SDL_Texture* water;

  int map[20][25];

};

#endif // MAP_H