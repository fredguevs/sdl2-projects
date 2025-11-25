#ifndef TEXTURE_MGR_H
#define TEXTURE_MGR_H

#include "Game.h"

class TextureManager
{
private:
  /* data */
public:
  TextureManager(/* args */);
  ~TextureManager();

  static SDL_Texture* LoadTexture(const char* filename, SDL_Renderer* renderer);
};



#endif // TEXTURE_MGR_H