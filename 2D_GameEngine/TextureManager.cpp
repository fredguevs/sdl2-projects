#include "TextureManager.h"

TextureManager::TextureManager(/* args */)
{
}

TextureManager::~TextureManager()
{
}

SDL_Texture* TextureManager::LoadTexture(const char* filename, SDL_Renderer* renderer) {
  SDL_Surface* tempSurface = IMG_Load(filename);
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
  
  SDL_FreeSurface(tempSurface);

  return texture;
}