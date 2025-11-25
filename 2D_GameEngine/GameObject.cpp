#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(const char* textureSheet,  int x, int y) {
  texture = TextureManager::LoadTexture(textureSheet);

  x_pos = (float)x;
  y_pos = (float)y;

  srcRect = {0, 0, 32, 32};
  destRect = { x, y, 64, 64 };

}

void GameObject::Update(float deltaTime){ 
  srcRect.h = 32;
  srcRect.w = 32;
  srcRect.x = 0;
  srcRect.y = 0;

  x_pos += speed * deltaTime;
  y_pos += speed * deltaTime;

  destRect.x = static_cast<int>(x_pos);
  destRect.y = static_cast<int>(y_pos);
  destRect.w = srcRect.w * 2;
  destRect.h = srcRect.h * 2;

}

void GameObject::Render() {
  SDL_RenderCopy(Game::renderer, texture, &srcRect, &destRect);
}