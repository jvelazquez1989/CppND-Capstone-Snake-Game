#ifndef BADGER_H
#define BADGER_H



class Badger {
 public:

  //Constructor
  Badger(int grid_width, int grid_height): grid_width(grid_width), 
                                                grid_height(grid_height){ }
  
  void UpdateBadger();

  //Direction direction = Direction::kUp;
  int direction{0};

  float speed{0.1f};
  float head_x{20};
  float head_y{20};

 private:
  void UpdateBadgerHead();
  int grid_width;
  int grid_height;  
};

#endif