#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H

#include "Components.h"
#include "../Vector2D.h"

class TransformComponent : public Component{

public:
  Vector2D position;
  Vector2D velocity;

  int height = 32; // default icon height
  int width = 32; // default icon width
  int scale = 1; // TODO: I think this should be a float, but I'll check later

  float speed = 3.0f;

  TransformComponent() {
    position.Zero();
  }

  TransformComponent(int sc) {
    position.Zero();
    scale = sc;
  }

  TransformComponent(float x, float y) {
    position.x = x;
    position.y = y;
  }

  TransformComponent(float x, float y, int h, int w, int sc) {
    position.x = x;
    position.y = y;
    height = h;
    width = w;
    scale = sc;
  }


  void init() override {
    velocity.Zero();
  }

  void update() override {
    position.x += velocity.x * speed;
    position.y += velocity.y * speed;
  }
};


#endif // TRANSFORM_COMPONENT_H