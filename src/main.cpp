#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include "score.h"

int main() {

  //Create Score object to keep track and record user score
  Score UserScore(0,0); //Initialize score and size to 0
  UserScore.setUserName();

  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game game(kGridWidth, kGridHeight);
  game.Run(controller, renderer, kMsPerFrame);

  //Record user score
  UserScore.setUserScoreData(game.GetScore(), game.GetSize());

  //Read previous high score data from file
  UserScore.ReadPreviousGameScoreData();

  //Write current user score data to file
  UserScore.WriteGameScoreData(); 

  std::cout << "Game has terminated successfully!\n";

  return 0;
}