#include "Game.h"
#include <iostream>

#include "TextureManager.h"
#include "GameObject.h"
#include "Map.h"


GameObject* player;

Map* map;

SDL_Renderer* Game::renderer = nullptr;


Game::Game() {}

Game::~Game() {}

void Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen){
  int flags = 0;
  if (fullscreen) {
    flags = SDL_WINDOW_FULLSCREEN;

  }
  if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
    std::cout << "Subsystems Initialized!..." << std::endl;
    
    window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

    if (window) {
      std::cout << "Window created" << std::endl;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (renderer) {
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
      SDL_RenderDrawPoint(renderer, xpos/2, ypos/2);

      std::cout << "Renderer created" << std::endl;
    }

    isRunning = true;
  }
  else {
    isRunning = false;
  }
  player = new GameObject("assets/player.png", 0, 0);
  map = new Map();
}

void Game::handleEvents() {
  SDL_Event event;

  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT:
        std::cout << "Quit Game called" << std::endl;
        isRunning = false;
        break;
    }
  }
}

void Game::update(float dt) {
  player->Update(dt);


  // destR.h = 64;
  // destR.w = 64;

  // destR.x = static_cast<int>(posX);


}

void Game::render(){
  // add stuff to render
  SDL_RenderClear(renderer);
  // add all textures to be rendered
  // painter's alg - render background, then entities
  map->DrawMap();
  player->Render();
  SDL_RenderPresent(renderer);
}

void Game::clean() {
  std::cout << "Killing window" << '\n';
  SDL_DestroyWindow(window);


  SDL_DestroyRenderer(renderer);
  SDL_Quit();
  std::cout << "Game Cleaned" << std::endl;
}
