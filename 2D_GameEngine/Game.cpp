#include "Game.h"
#include <iostream>

#include "TextureManager.h"
#include "GameObject.h"
#include "Map.h"

#include "ECS/Components.h"
#include "Vector2D.h"

#include "Collision.h"


Map* map;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

auto& player(manager.addEntity());
auto& wall(manager.addEntity());

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
      SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
      SDL_RenderDrawPoint(renderer, xpos/2, ypos/2);
      SDL_RenderSetScale(renderer, 1.8, 1.8);

      std::cout << "Renderer created" << std::endl;
    }

    isRunning = true;
  }
  else {
    isRunning = false;
  }
  map = new Map();

  //ecs implementation

  player.addComponent<TransformComponent>(2);
  player.addComponent<SpriteComponent>("assets/player.png");
  player.addComponent<KeyboardController>();
  player.addComponent<ColliderComponent>("player");

  wall.addComponent<TransformComponent>(300.0f, 300.0f, 300, 20, 1);
  wall.addComponent<SpriteComponent>("assets/dirt.png");
  wall.addComponent<ColliderComponent>("wall");

}

void Game::handleEvents() {

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

  manager.refresh();
  manager.update();


  if (Collision::AABB(player.getComponent<ColliderComponent>().collider, wall.getComponent<ColliderComponent>().collider))
  {
    std::cout << "player and wall hit !" << '\n';
  }

}

void Game::render(){
  // add stuff to render
  SDL_RenderClear(renderer);
  // add all textures to be rendered
  // painter's alg - render background, then entities
  map->DrawMap();

  manager.draw();
  SDL_RenderPresent(renderer);
}

void Game::clean() {
  std::cout << "Killing window" << '\n';
  SDL_DestroyWindow(window);


  SDL_DestroyRenderer(renderer);
  SDL_Quit();
  std::cout << "Game Cleaned" << std::endl;
}
