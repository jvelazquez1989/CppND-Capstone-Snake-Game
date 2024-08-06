#include "food.h"
#include "SDL.h"

#include <iostream>

//setFoodPosition sets the x and y coordinates of the food
void Food::setFoodPosition(int x, int y)
{
    x_pos = x;
    y_pos = y;
    food.x = x;
    food.y = y;

    //std::cout << "setFoodPosition called | food.x = " << food.x << " | food.y = " << food.y << "\n";
}

//setMoveFlag sets the move flag to the requested setting
void Food::setMoveFlag(bool move_rq){move = move_rq;}

//setEatFlag sets the eat flag to the requested state
void Food::setEatFlag(bool eat_state){eat = eat_state;}




//getFoodPosition returns the x and y coordinates of the food
std::vector<int> Food::getFoodPosition()
{
    
    std::vector<int> food_position;
    food_position.push_back(x_pos);
    food_position.push_back(y_pos);
    //std::cout << "getFoodPosition called | food_position[0] = " << food_position[0] << " | food_position[1] = " << food_position[1] << "\n";    

    return food_position;
}


//getFoodColor returns the values of R G B of the food
std::vector<int> Food::getFoodColor()
{
     std::vector<int> food_color;
     food_color.push_back(R);
     food_color.push_back(G);
     food_color.push_back(B);

     return food_color;
}

//getScorePoints returns the number of points to add when food is eaten
int Food::getScorePoints() {return score_points;}

//getSpeedGain returns the speed gained from eating the food
float Food::getSpeedGain() {return speed_gain;}

//getTimeToMoveFood returns the amount of time before the food will be moved to a new position
float Food::getTimeToMoveFood() {return timer;}

//getEatFlagState returns the current state of the eat flag
bool Food::getEatFlagState() {return eat;}

//getMoveFlagState returns the current state of the move flag
bool Food::getMoveFlagState() {return move;}
