#include "renderer.h"
#include <iostream>
#include <string>

#include <vector>


Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

//void Renderer::Render(Snake const snake, SDL_Point const &food, SDL_Point const &green_food, SDL_Point const &purple_food, Food *yellow_food) {
//void Renderer::Render(Snake const snake, SDL_Point const &food, SDL_Point const &green_food, SDL_Point const &purple_food, std::shared_ptr<Food> yellow_food) {
void Renderer::Render(Snake const snake, Badger const badger, std::shared_ptr<Food> green_food, std::shared_ptr<Food> purple_food, std::shared_ptr<Food> yellow_food) {

  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;
  
  std::vector<int> food_color;
  std::vector<int> food_pos;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  // Render GREEN food (new code)
  food_color = green_food->getFoodColor();
  SDL_SetRenderDrawColor(sdl_renderer, food_color[0], food_color[1], food_color[2], 0xFF);
  food_pos = green_food->getFoodPosition();
  block.x = food_pos[0] * block.w;
  block.y = food_pos[1] * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);

  // Render PURPLE food (new code)
  food_color = purple_food->getFoodColor();
  SDL_SetRenderDrawColor(sdl_renderer, food_color[0], food_color[1], food_color[2], 0xFF);
  food_pos = purple_food->getFoodPosition();
  block.x = food_pos[0] * block.w;
  block.y = food_pos[1] * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);

  // Render YELLOW food (new code)
  food_color = yellow_food->getFoodColor();
  SDL_SetRenderDrawColor(sdl_renderer, food_color[0], food_color[1], food_color[2], 0xFF);
  food_pos = yellow_food->getFoodPosition();
  block.x = food_pos[0] * block.w;
  block.y = food_pos[1] * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);

  // Render snake's body
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  for (SDL_Point const &point : snake.body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render snake's head
  block.x = static_cast<int>(snake.head_x) * block.w;
  block.y = static_cast<int>(snake.head_y) * block.h;
  if (snake.alive) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(sdl_renderer, &block);

  //Render badger's head
  block.x = static_cast<int>(badger.head_x) * block.w;
  block.y = static_cast<int>(badger.head_y) * block.h;
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  SDL_RenderFillRect(sdl_renderer, &block);

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
