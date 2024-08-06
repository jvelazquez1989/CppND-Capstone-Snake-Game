#include "game.h"
#include <iostream>
#include "SDL.h"


Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)) {
  PlaceFood();
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  Uint32 green_food_frame_timestamp = SDL_GetTicks();  
  int green_food_frame_count = 0;

  Uint32 purple_food_frame_timestamp = SDL_GetTicks();  
  int purple_food_frame_count = 0;

  Uint32 orange_food_frame_timestamp = SDL_GetTicks();  
  int orange_food_frame_count = 0;
 
  //std::cout << "check point 1" << "\n";

  while (running) {
    frame_start = SDL_GetTicks();    

    // Input, Update, Render - the main game loop.
    //std::cout << "check point 2" << "\n";
    controller.HandleInput(running, snake);
    //std::cout << "orange_food pointer = " << orange_food << "\n";
    //std::cout << "check point 3" << "\n";
    Update();
    //std::cout << "check point 4" << "\n";
    //renderer.Render(snake, food, green_food, purple_food, orange_food); //new code
    renderer.Render(snake, food, green_food, purple_food, orange_food); //new code
    //std::cout << "check point 5" << "\n";

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    green_food_frame_count++; //increment green food frame count
    purple_food_frame_count++; //increment purple food frame count
    orange_food_frame_count++;
    frame_duration = frame_end - frame_start;
    

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // Reset green food timer if green food has been eaten
    if(eat_green_food)
    {
      eat_green_food = false;
      green_food_frame_count = 0;
      green_food_frame_timestamp = frame_end;
    }

     // Reset purple food timer if green food has been eaten
    if(eat_purple_food)
    {
      eat_purple_food = false;
      purple_food_frame_count = 0;
      purple_food_frame_timestamp = frame_end;
    }

       // After every 4 seconds, set flag to move green food.
    if (frame_end - green_food_frame_timestamp >= 4000) {
      move_green_food = true;      
      green_food_frame_count = 0;
      green_food_frame_timestamp = frame_end;
    }   

    // After every 1.5 seconds, set flag to move green food.
    if (frame_end - purple_food_frame_timestamp >= 1500) {
      move_purple_food = true;      
      purple_food_frame_count = 0;
      purple_food_frame_timestamp = frame_end;
    }




      // Reset orange food timer if green food has been eaten
    if(orange_food->getEatFlagState())
    {
      //eat_purple_food = false;
      orange_food->setEatFlag(false);
      orange_food_frame_count = 0;
      orange_food_frame_timestamp = frame_end;
    }

    // After every 1.5 seconds, set flag to move green food.
    if (frame_end - orange_food_frame_timestamp >= orange_food->getTimeToMoveFood()*1000) {
      //move_purple_food = true;  
      orange_food->setMoveFlag(true);    
      orange_food_frame_count = 0;
      orange_food_frame_timestamp = frame_end;
    }

    

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y)) {
      food.x = x;
      food.y = y;
      return;
    }
  }
}

void Game::Update() {
  if (!snake.alive) return;

  snake.Update();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    score++;
    PlaceFood();    
    // Grow snake and increase speed.
    snake.GrowBody();
    snake.speed += 0.01;
  }

  // Check if there's green food over here
  if (green_food.x == new_x && green_food.y == new_y) {
    score += 2;//increase score by 2 points
    PlaceGreenFood();
    move_green_food = false; //reset move flag
    eat_green_food = true; //green food has been eaten
    // Grow snake and increase speed.
    snake.GrowBody();
    snake.speed += 0.02;
  }

  // Check if there's purple food over here
  if (purple_food.x == new_x && purple_food.y == new_y) {
    score += 5;//increase score by 5 points
    PlacePurpleFood();
    move_purple_food = false; //reset move flag
    eat_purple_food = true; //purple food has been eaten
    // Grow snake and increase speed.
    snake.GrowBody();
    snake.speed += 0.03;
  }

  // Move green food if green food timer expires
  if(move_green_food)
  {
    PlaceGreenFood();
    move_green_food = false;
  }

  // Move purple food if purple food timer expires
  if(move_purple_food)
  {
    PlacePurpleFood();
    move_purple_food = false;
  }

   // Check if there's orange food over here
  //std::cout << "checkpoint  3a" << "\n";
  std::vector<int> food_pos = orange_food->getFoodPosition();
  //std::vector<int> food_pos = 
  //std::cout << "checkpoint  3b" << "\n";
  
  if (food_pos[0] == new_x && food_pos[1] == new_y) {
    ///std::cout << "orange food eaten" << "\n";
    //std::cout << "food pos x = " << food_pos[0] << " food pos y = " << food_pos[1] << "\n";
    //score++;//increase score by 5 points
    score += orange_food->getScorePoints();
    //PlaceNewFood(orange_food);
    PlaceNewFood(orange_food);
    orange_food->setMoveFlag(false);
    orange_food->setEatFlag(true);
    //move_purple_food = false; //reset move flag
    //eat_purple_food = true; //purple food has been eaten
    // Grow snake and increase speed.
    snake.GrowBody();
    //snake.speed += 0.01;
    snake.speed  += orange_food->getSpeedGain();
  }

  // Move orange food if purple food timer expires
  if(orange_food->getMoveFlagState())
  {
    PlaceNewFood(orange_food);
    orange_food->setMoveFlag(false);
  }


}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }



void Game::PlaceGreenFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y)) {
      green_food.x = x;
      green_food.y = y;
      return;
    }
  }
}

void Game::PlacePurpleFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y)) {
      purple_food.x = x;
      purple_food.y = y;
      return;
    }
  }
}


//void Game::PlaceNewFood(Food *food) {
void Game::PlaceNewFood(std::shared_ptr<Food> food) {

  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y)) {
      food->setFoodPosition(x, y);
      return;
    }
  }
}