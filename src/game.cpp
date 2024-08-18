#include "game.h"
#include <iostream>
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)) {
  yellow_food = std::make_shared<Food>(16, 10, 0xFF, 0xCC, 0x00, 1, 0.01, 10);
  green_food = std::make_shared<Food>(1, 16, 0x7C, 0xFC, 0x00, 2, 0.02, 5);
  purple_food = std::make_shared<Food>(30, 16, 0x94, 0x00, 0xD3, 4, 0.04, 2.5);
  pBadger = std::make_shared<Badger>(grid_width,grid_height);
  badger_thread = std::thread(&Badger::UpdateBadger, pBadger); //launch thread for badger
}

Game::~Game()
{
  badger_thread.join();
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

  Uint32 yellow_food_frame_timestamp = SDL_GetTicks();  
  int yellow_food_frame_count = 0; 


  while (running) {
    frame_start = SDL_GetTicks();    

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake);
    Update();
    renderer.Render(snake, green_food, purple_food, yellow_food, pBadger); //new code

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    green_food_frame_count++; //increment green food frame count
    purple_food_frame_count++; //increment purple food frame count
    yellow_food_frame_count++;
    frame_duration = frame_end - frame_start;
    

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    } 

    // Reset green food timer if food has been eaten
    if(green_food->getEatFlagState())
    {
      green_food->setEatFlag(false);
      green_food_frame_count = 0;
      green_food_frame_timestamp = frame_end;
    }

    // After every few seconds, set flag to move green food.
    if (frame_end - green_food_frame_timestamp >= green_food->getTimeToMoveFood()) { 
      green_food->setMoveFlag(true);    
      green_food_frame_count = 0;
      green_food_frame_timestamp = frame_end;
    }

    // Reset purple food timer if  food has been eaten
    if(purple_food->getEatFlagState())
    {
      purple_food->setEatFlag(false);
      purple_food_frame_count = 0;
      purple_food_frame_timestamp = frame_end;
    }

    // After every few seconds, set flag to move purple food.
    if (frame_end - purple_food_frame_timestamp >= purple_food->getTimeToMoveFood()) { 
      purple_food->setMoveFlag(true);    
      purple_food_frame_count = 0;
      purple_food_frame_timestamp = frame_end;
    }

    // Reset yellow food timer if  food has been eaten
    if(yellow_food->getEatFlagState())
    {
      //eat_purple_food = false;
      yellow_food->setEatFlag(false);
      yellow_food_frame_count = 0;
      yellow_food_frame_timestamp = frame_end;
    }

    // After every few seconds, set flag to move yellow food.
    if (frame_end - yellow_food_frame_timestamp >= yellow_food->getTimeToMoveFood()) {
      //move_purple_food = true;  
      yellow_food->setMoveFlag(true);    
      yellow_food_frame_count = 0;
      yellow_food_frame_timestamp = frame_end;
    }    

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}


void Game::Update() {
  if (!snake.alive) return;
  
  snake.Update();

  //read badger data under lock
  std::lock_guard<std::mutex> lock(mtx);
  pBadger->UpdateBadger();
  if(snake.SnakeCell(pBadger->head_x, pBadger->head_y)){snake.alive = false;} // Check if badger has eaten snake

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);
  std::vector<int> food_pos;
  

  // Check if there's yellow food over here
  food_pos = yellow_food->getFoodPosition();
  //std::cout << "checkpoint  3b" << "\n";  
  if (food_pos[0] == new_x && food_pos[1] == new_y) {
    //increase score
    score += yellow_food->getScorePoints();
    PlaceNewFood(yellow_food);
    yellow_food->setMoveFlag(false);
    yellow_food->setEatFlag(true);

    // Grow snake and increase speed.
    snake.GrowBody();
    snake.speed  += yellow_food->getSpeedGain();
  }

  // Move yellow food if food timer expires
  if(yellow_food->getMoveFlagState())
  {
    PlaceNewFood(yellow_food);
    yellow_food->setMoveFlag(false);
  }


  // Check if there's green food over here
  food_pos = green_food->getFoodPosition();
  if (food_pos[0] == new_x && food_pos[1] == new_y) {
    //increase score
    score += green_food->getScorePoints();
    
    //place new food on the map
    PlaceNewFood(green_food);
    green_food->setMoveFlag(false);
    green_food->setEatFlag(true);

    // Grow snake and increase speed.
    snake.GrowBody();
    snake.speed  += green_food->getSpeedGain();
  }

  // Move green food if food timer expires
  if(green_food->getMoveFlagState())
  {
    PlaceNewFood(green_food);
    green_food->setMoveFlag(false);
  }


  // Check if there's purple food over here
  food_pos = purple_food->getFoodPosition();
  if (food_pos[0] == new_x && food_pos[1] == new_y) {
    //increase score
    score += purple_food->getScorePoints();
    
    //place new food on the map
    PlaceNewFood(purple_food);
    purple_food->setMoveFlag(false);
    purple_food->setEatFlag(true);

    // Grow snake and increase speed.
    snake.GrowBody();
    snake.speed  += purple_food->getSpeedGain();
  }

  // Move purple food if food timer expires
  if(purple_food->getMoveFlagState())
  {
    PlaceNewFood(purple_food);
    purple_food->setMoveFlag(false);
  }



}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }


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