#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <iostream>

class Game {
public:
  Game();
  ~Game();

  float posX = 0.0f;
  float speed = 20.0f;

  void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

  void handleEvents();
  void update(float dt);
  void render();
  void clean();

  bool running() {return isRunning; };

private:
  bool isRunning;
  SDL_Window *window;
  SDL_Renderer *renderer;

};

#endif