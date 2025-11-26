#ifndef SPRITE_H
#define SPRITE_H

#include "Components.h"
#include "SDL2/SDL.h"

class SpriteComponent : public Component {
private:
  TransformComponent *transform;
  SDL_Texture *texture;
  SDL_Rect srcRect, dstRect;


public:
  SpriteComponent() = default;
  SpriteComponent(const char* path) {
    setTex(path);
  }

  void init() override {
    transform = &entity->getComponent<TransformComponent>();

    srcRect.x = srcRect.y = 0;
    srcRect.w = srcRect.h = 32;
    dstRect.w = dstRect.h = 64;
  }

  void setTex(const char* path) {
    texture = TextureManager::LoadTexture(path);
  }

  void update() override {
    dstRect.x = (int)transform->position.x;
    dstRect.y = (int)transform->position.y;
  }

  void draw() override {
    TextureManager::Draw(texture, srcRect, dstRect);
  }


};


#endif // SPRITE_H