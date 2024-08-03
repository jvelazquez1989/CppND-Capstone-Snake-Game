#include "score.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>


// setUserName prompts the user to enter name and will write to user_name
void Score::setUserName()
{
    std::string name;
    std::cout << "----------------------------------------" << "\n";
    std::cout << "Enter User Name: ";
    std::getline(std::cin, name);
    std::cout << "----------------------------------------" << "\n";

    if(name.length() == 0)
    {
        std::cout << "No user name detected! Setting user name to: Player 1" << "\n";
        user_name = "Player_1";
            
    }
    else
    {
        std::cout << "Launching the game..." << "\n";

        //Replace spaces with underscores
       for(int i = 0; i < name.length(); i++)
       {
           if(name[i] == ' '){name[i] = '_';}
       }       
        
        //Assign to user_name private variable
        user_name = name;
    }
}


// setUserScore writes user score to user_core
void Score::setUserScoreData(int const score, int const size)
{
    user_score = std::max(0, score);
    snake_size = std::max(0, size);
}

/// ReadPreviousGameScoreData reads previous data from score file
void Score::ReadPreviousGameScoreData()
{
    std::string line;
    std::vector<std::string> name;
    std::vector<int> score;
    std::vector<int> size;

    std::string temp_name;
    int temp_score;
    int temp_size;
    
    std::ifstream input_file("../src/game_score.txt");
    if(input_file.is_open())
    {
        while(std::getline(input_file, line))
        {
            std::istringstream linestream(line);
            linestream >> temp_name >> temp_score >> temp_size;
            
            name.push_back(temp_name);
            score.push_back(temp_score);
            size.push_back(temp_size);
        }        
    }

    /*for(int i = 0; i < name.size(); i++){
        std::cout << "name = " << name[i] << " | score = " << score[i] << " | size = " << size[i] << "\n";
    }*/

    for(int i = 0; i < score.size(); i++)
    {
        for(int j = i + 1; j < score.size(); j++)
        {
            temp_name = "user";
            temp_size = 0;
            temp_score = 0;
            if (score[i] < score[j])
            {
                //Swap indeces of the vectors if the current score is smaller than the next one
                temp_name = name[i];
                name[i] = name[j];
                name[j] = temp_name;

                temp_score = score[i];
                score[i] = score[j];
                score[j] = temp_score;

                temp_size = size[i];
                size[i] = size[j];
                size[j] = temp_size;
            }
        }
    }

    //Set record score data
    setRecordScoreData(name[0], score[0], size[0]);
   

    /*for(int i = 0; i < name.size(); i++){
         std::cout << "Sorted list" << "\n";
        std::cout << "name = " << name[i] << " | score = " << score[i] << " | size = " << size[i] << "\n";
    }*/

    std::cout << "-----------------Previous High Score-----------------------" << "\n";
    std::cout << "User Name: " << name[0] << "\n";
    std::cout << "High Score: " << score[0] << "\n";
    std::cout << "Snake Size: " << size[0] << "\n";
    std::cout << "-----------------------------------------------------------" << "\n";
}


// setHighScoreData records the record data to private variables
void Score::setRecordScoreData(std::string const name, int const score, int const size)
{
    record_user_name = name;
    record_score = std::max(0, score);
    record_size = std::max(0, size);
}


// getUserScoreData returns the user's score data stored in private variables
std::string Score::getUserScoreData()
{
    std::string score_data = user_name + " " + std::to_string(user_score) + " " + std::to_string(snake_size);
    return score_data;
}


// getRecordScoreData returns the record high score data stored in private variables
std::string Score::getRecordScoreData()
{
    std::string record_score_data = record_user_name + " " + std::to_string(record_score) + " " + std::to_string(record_size);
    return record_score_data;
}


// WriteGameScoreData writes the user data to game score file
void Score::WriteGameScoreData()
{
    std::string user_score_data = getUserScoreData();
    std::string record_score_data = getRecordScoreData();

    //std::cout << "User Score Data = " << user_score_data << "\n";
    //std::cout << "Record Score Data = " << record_score_data << "\n";

    std::string name, record_name;
    int score, record_score;
    int size, record_size;

    std::istringstream score_linestream(user_score_data);
    score_linestream >> name >> score >> size;

    std::istringstream record_linestream(record_score_data);
    record_linestream >> record_name >> record_score >> record_size;

    std::cout << "-----------------Game Results-----------------------" << "\n";
    std::cout << "User Name: " << name << "\n";
    std::cout << "High Score: " << score << "\n";
    std::cout << "Snake Size: " << size << "\n";
    std::cout << "-----------------------------------------------------------" << "\n";

    if(score > record_score)
    {
        std::cout << "************ NEW HIGH SCORE! ************" << "\n";
        std::cout << "User Name: " << name << "\n";
        std::cout << "New High Score: " << score << "\n";
        std::cout << "Snake Size: " << size << "\n";
        std::cout << "*****************************************" << "\n";

        setRecordScoreData(name, score, size);
    }

    //Write new data to file
    std::ofstream file;
    file.open("../src/game_score.txt", std::ios::app);
    file << user_score_data << std::endl;
    file.close();
}