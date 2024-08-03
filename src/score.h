#ifndef SCORE_H
#define SCORE_H

#include <iostream>
#include <string>

class Score {
    public:
    //Constructor
    Score(int score, int size){setUserScoreData(score, size);}

    //Define setters
    void setUserName();
    void setUserScoreData(int const score, int const size);
    void setRecordScoreData(std::string const name, int const score, int const size);

    //Define getters
    std::string getUserScoreData();
    std::string getRecordScoreData();

    //Functions
    void ReadPreviousGameScoreData();
    void WriteGameScoreData();

    private:
    int user_score;
    int snake_size;
    std::string user_name;
    int record_score;
    int record_size;
    std::string record_user_name;

};

#endif