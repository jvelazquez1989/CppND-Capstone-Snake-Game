#include "badger.h"
#include <cmath>
#include <iostream>

void Badger::UpdateBadger()
{    
    direction += std::rand() % (5+1);
    if(direction > 1000) {direction = std::rand() % (500+1);}
    UpdateBadgerHead();
}

void Badger::UpdateBadgerHead()
{
  if(direction <= 250){head_y -= speed;} //move up
  else if(direction > 250 && direction <= 500){head_x += speed;} //move right
  else if(direction > 500 && direction <= 750){head_y += speed;} //move down
  else {head_x -= speed;} //move left

  // Wrap the Badger around to the beginning if going off of the screen.
  head_x = fmod(head_x + grid_width, grid_width);
  head_y = fmod(head_y + grid_height, grid_height);
}