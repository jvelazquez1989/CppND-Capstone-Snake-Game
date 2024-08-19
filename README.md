# CPPND: Capstone Snake Game Example

This is a starter repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). The code for this repo was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

<img src="snake_game.gif"/>

The Capstone Project gives you a chance to integrate what you've learned throughout this program. This project will become an important part of your portfolio to share with current and future colleagues and employers.

In this project, you can build your own C++ application or extend this Snake game, following the principles you have learned throughout this Nanodegree Program. This project will demonstrate that you can independently create applications using a wide range of C++ features.

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  >Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source. 
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.


## CC Attribution-ShareAlike 4.0 International


Shield: [![CC BY-SA 4.0][cc-by-sa-shield]][cc-by-sa]

This work is licensed under a
[Creative Commons Attribution-ShareAlike 4.0 International License][cc-by-sa].

[![CC BY-SA 4.0][cc-by-sa-image]][cc-by-sa]

[cc-by-sa]: http://creativecommons.org/licenses/by-sa/4.0/
[cc-by-sa-image]: https://licensebuttons.net/l/by-sa/4.0/88x31.png
[cc-by-sa-shield]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg


## New Features
1. Players can add their names and the game can save their high scores

2. The game will randomly add three different types of food on the map:
    a) Yellow = 1 point + 0.1 speed
    b) Green = 2 points + 0.2 speed
    c) Purple = 4 points + 0.4 speed

3. The snake will need to watch out for a honey badger on the hunt!
    A honey badger (pink) will randomly walk the game map
    If the honey badger touches any part of the snake, the snake dies
    The honey badger speed will slowly increase as the game progresses

## Rubric Evidence - Loops, Functions, I/O
### The project accepts user input and processes the input.
- `score.h` and `score.cpp` prompt the user for input and processes the data for the game session
- `main.cpp` line 11 triggers prompt for user to enter their name
- `setUserName()` function processes the user input to make sure the user has entered a name. The function also deletes any spaces and replaces it with an underscore

### The project reads data from a file and process the data, or the program writes data to a file.
- `score.h` and 'score.cpp' writes the user name, score, and snake size to game_score.txt
- `ReadPreviousGameScoreData()` parses game_score.txt to find the previous high score data
- `WriteGameScoreData()` writes the user score data to game_score.txt and also reports if the current user score is the new high score

## Rubric Evidence - Object Oriented Programing
### One or more classes are added to the project with appropriate access specifiers for class members.
- `food.h` and 'food.cpp' create a new class 'Food' to hold all of the data related to food items. This allows for multiple food objects to be easily created and placed on the map with different settings such as color, speed, and points

### Class constructors utilize member initialization lists.
- `Food` constructor initializes private variables with initialization lists

### Classes abstract implementation details from their interfaces.
- `food.h` and `food.cpp` abstract the implementation details and clearly documents the function effect via the function name for Food objects
- `score.h` and `score.cpp` abstract the implementation details and clearly documents the function effect via the function name for Score objects

## Rubric Evidence - Memory Management
### The project makes use of references in function declarations.
- `PlaceNewFood(td::shared_ptr<Food> &food)` in `game.cpp` passes a Food object by reference to avoid creating an internal copy

### The project uses destructors appropriately
- `game.cpp` uses the class destructor `~Game()` to join the badger thread back into the main thread before closing the program

### The project uses smart pointers instead of raw pointers.
- `game.h` uses shared pointers `yellow_food`, `green_food`, and `purple_food` for each of the three food objects. The pointers are used by `game.cpp` to access and update food item data


## Rubric Evidence - Concurrency
### The project uses multithreading.
- `badger.h` and `badger.cpp` create a Badger class which is used to run the badger on a separate thread
- `game.h` defines a smart pointer to a badger object and a thread to run the badger object
- `game.cpp` lines 13 and 14 create the badger object and thread

### A mutex or lock is used in the project
- `game.cpp` uses a `lock_guard` to read the badger head x and y position under lock




