#ifndef COLLIDER_H
#define COLLIDER_H

#include <string>
#include "SDL2/SDL.h"
#include "ECS.h"
#include "Components.h"

class ColliderComponent : public Component {
public:
  SDL_Rect collider;

  // when we detect collision, get tag of object and figure out what action to take
  std::string tag;

  TransformComponent* transform;

  ColliderComponent() = default;

  ColliderComponent(std::string tag_in) {
    tag = tag_in; 
  }

  void init() override {
    // check to prevent runtime error
    if (!entity->hasComponent<TransformComponent>()) {
      entity->addComponent<TransformComponent>();
    }
    transform = &entity->getComponent<TransformComponent>();
  }

  void update() override {
    collider.x = static_cast<int>(transform->position.x);
    collider.y = static_cast<int>(transform->position.y);
    collider.w = transform->width * transform->scale;
    collider.h = transform->height * transform->scale;
  }

};


#endif // COLLIDER_H