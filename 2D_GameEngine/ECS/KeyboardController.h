#ifndef KEYBOARD_CONTROLLER_H
#define KEYBOARD_CONTROLLER_H

#include "../Game.h"
#include "ECS.h"
#include "Components.h"

class KeyboardController : public Component {
public:
  TransformComponent *transform;
  
  void init() override {
    transform = &entity->getComponent<TransformComponent>();

  }
  
  void update() override {
    const Uint8* keystates = SDL_GetKeyboardState(NULL);
    
    transform->velocity.x = 0;
    transform->velocity.y = 0;
    
    if (keystates[SDL_SCANCODE_W]) {
      transform->velocity.y = -1;
    }
    if (keystates[SDL_SCANCODE_S]) {
      transform->velocity.y = 1;
    }
    if (keystates[SDL_SCANCODE_A]) {
      transform->velocity.x = -1;
    }
    if (keystates[SDL_SCANCODE_D]) {
      transform->velocity.x = 1;
    }
  }


};


#endif // KEYBOARD_CONTROLLER_H