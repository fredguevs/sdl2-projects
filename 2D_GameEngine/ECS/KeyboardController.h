#ifndef KEYBOARD_CONTROLLER_H
#define KEYBOARD_CONTROLLER_H

#include "../Game.h"
#include "ECS.h"
#include "Components.h"
#include <cmath>

class KeyboardController : public Component {
public:
  TransformComponent *transform;
  
  void init() override {
    transform = &entity->getComponent<TransformComponent>();

  }
  
  void update() override {
    const Uint8* keystates = SDL_GetKeyboardState(NULL);

    float dx = 0.0f;
    float dy = 0.0f;

    if (keystates[SDL_SCANCODE_W]) {
      dy -= 1.0f;
    }
    if (keystates[SDL_SCANCODE_S]) {
      dy += 1.0f;
    }
    if (keystates[SDL_SCANCODE_A]) {
      dx -= 1.0f;
    }
    if (keystates[SDL_SCANCODE_D]) {
      dx += 1.0f;
    }

    // normalize so diagonals aren't faster
    float len = std::sqrt(dx*dx + dy*dy);
    if (len > 0.0f) {
      dx /= len;
      dy /= len;
    }

    transform->velocity.x = dx;
    transform->velocity.y = dy;
  }


};


#endif // KEYBOARD_CONTROLLER_H