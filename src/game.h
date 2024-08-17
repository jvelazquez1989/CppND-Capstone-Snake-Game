#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"

#include "food.h"
#include <memory>
#include "badger.h"

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;

 private:
  Snake snake;
  Badger badger;

  std::shared_ptr<Food> green_food;
  std::shared_ptr<Food> purple_food;
  std::shared_ptr<Food> yellow_food;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};

  void PlaceNewFood(std::shared_ptr<Food> food); //new code
  void Update();
};

#endif