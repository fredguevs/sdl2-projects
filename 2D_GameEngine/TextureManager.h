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

  static SDL_Texture* LoadTexture(const char* filename);

  static void Draw(SDL_Texture* texture, SDL_Rect src, SDL_Rect dst);
};



#endif // TEXTURE_MGR_H