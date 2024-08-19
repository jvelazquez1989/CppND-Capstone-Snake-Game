#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include "SDL.h"

class Snake {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  Snake(int grid_width, int grid_height)
      : grid_width(grid_width),
        grid_height(grid_height),
        head_x(grid_width / 2),
        head_y(grid_height / 2) {}
  
  //Copy constructor
  ///Snake(const Snake &source){}
  Snake(const Snake &source)
  {
    direction = source.direction;
    speed = source.speed;
    size = source.size;
    alive = source.alive;
    head_x = source.head_x;
    head_y = source.head_y;
    body = source.body;
    
    growing = source.growing;
    grid_width = source.grid_width;
    grid_height = source.grid_height;
  }

  void Update();

  void GrowBody();
  bool SnakeCell(int x, int y);

  Direction direction = Direction::kUp;

  float speed{0.1f};
  int size{1};
  bool alive{true};
  float head_x;
  float head_y;
  std::vector<SDL_Point> body;

 private:
  void UpdateHead();
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);

  bool growing{false};
  int grid_width;
  int grid_height;
};

#endif