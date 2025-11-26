#include "Game.h"

Game *game = nullptr;

int main(int argc, const char * argv[]) {
  game = new Game();

  game->init("Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 1000, false);

  Uint32 lastTime = SDL_GetTicks();
  float deltaTime = 0.0f;

  while (game->running()) {
    Uint32 now = SDL_GetTicks(); // ms its been since we first initialized SDL
    deltaTime = (now - lastTime) / 1000.0f; // convert ms to seconds
    lastTime = now;

    game->handleEvents();
    game->update(deltaTime);
    game->render();
  }

  game->clean();
  

  return 0;
}