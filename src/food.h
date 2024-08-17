#ifndef FOOD_H
#define FOOD_H

#include "SDL.h"
#include <vector>

class Food{
    public:
    //Constructor
    Food(int x, int y, int const r, int const g, int const b, int const points, float const speed, float time): R(r), G(g), B(b), score_points(points), speed_gain(speed), timer(time*1000) {
        setFoodPosition(x, y);
        //setFoodColor(r, g, b);
    }

    //getters
    std::vector<int> getFoodPosition();
    std::vector<int> getFoodColor();
    int getScorePoints();
    float getSpeedGain();
    float getTimeToMoveFood();
    bool getEatFlagState();
    bool getMoveFlagState();

    
    //setters
    void setFoodPosition(int x, int y);
    void setMoveFlag(bool move_rq);
    void setEatFlag(bool eat_state);    
    

    private:
    SDL_Point food;
    int x_pos{0}; //x position of food
    int y_pos{0}; //y position of food
    int const R{0x00}; // RGB color settings
    int const G{0x00};
    int const B{0x00};
    float timer; //timer threshold for food to move
    bool move{false}; //flag indicating food needs to move position
    bool eat{true}; //flag indicating food has been eaten
    int const score_points{0}; //number of points gained for eating food
    float const speed_gain{0.01}; //Additional snake speed gained for eating food

};
#endif