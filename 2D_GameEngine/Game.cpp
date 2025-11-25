#include "Game.h"
#include <iostream>

#include "TextureManager.h"

SDL_Texture* playerTex;
SDL_Rect srcR, destR;


Game::Game() {}

Game::~Game() {}

void Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen){
  int flags = 0;
  if (fullscreen) {
    flags = SDL_WINDOW_FULLSCREEN;

  }
  if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
    std::cout << "Subsystems Initialized!..." << std::endl;
    
    window = SDL_CreateWindow(title, xpos, ypos, width, height, fullscreen);
    
    
    if (window) {
      std::cout << "Window created" << std::endl;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    

    if (renderer) {
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
      SDL_RenderSetScale(renderer, 2, 2);
      SDL_RenderDrawPoint(renderer, xpos/2, ypos/2);


      std::cout << "Renderer created" << std::endl;
    }

    isRunning = true;
  }
  else {
    isRunning = false;
  }
  playerTex = TextureManager::LoadTexture("assets/player.png", renderer);
}

void Game::handleEvents() {
  SDL_Event event;
  SDL_PollEvent(&event);

  switch (event.type) {
    case SDL_QUIT:
      isRunning = false;
      break;
  
    default:
      break;
  }
}

void Game::update(float dt) {
  posX += speed * dt;

  destR.h = 64;
  destR.w = 64;

  destR.x = static_cast<int>(posX);


}

void Game::render(){
  // add stuff to render
  SDL_RenderClear(renderer);
  // add all textures to be rendered
  // painter's alg - render background, then entities
  SDL_RenderCopy(renderer, playerTex, NULL, &destR);
  SDL_RenderPresent(renderer);
}

void Game::clean() {
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
  std::cout << "Game Cleaned" << std::endl;
}
