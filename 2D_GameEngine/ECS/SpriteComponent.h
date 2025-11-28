#ifndef SPRITE_H
#define SPRITE_H

#include "Components.h"
#include "SDL2/SDL.h"
#include "../TextureManager.h"

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

  ~SpriteComponent() {
    SDL_DestroyTexture(texture);
  }

  void init() override {
    transform = &entity->getComponent<TransformComponent>();

    srcRect.x = srcRect.y = 0;
    srcRect.w = transform->width;
    srcRect.h = transform->height;
  }

  void setTex(const char* path) {
    texture = TextureManager::LoadTexture(path);
  }

  void update() override {
    dstRect.x = static_cast<int>(transform->position.x);
    dstRect.y = static_cast<int>(transform->position.y);
    dstRect.w = static_cast<int>(transform->width * transform->scale);
    dstRect.h = static_cast<int>(transform->height * transform->scale);
  }

  void draw() override {
    TextureManager::Draw(texture, srcRect, dstRect);
  }


};


#endif // SPRITE_H