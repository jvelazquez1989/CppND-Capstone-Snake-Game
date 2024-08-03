#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;

 private:
  Snake snake;
  SDL_Point food;
  SDL_Point green_food; //new code
  SDL_Point purple_food; //new code

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};

  void PlaceFood();
  void PlaceGreenFood(); //new code
  void PlacePurpleFood(); //new code
  void Update();

  bool move_green_food{false}; //Flag indicating green food needs to be moved to new location
  bool eat_green_food{true}; //Flag indicating green food has been eaten
  bool move_purple_food{false}; //Flag indicating purple food needs to be moved to new location
  bool eat_purple_food{true}; //Flag indicating purple food has been eaten
};

#endif