#ifndef SCORE_H
#define SCORE_H

#include "../subject/subject.h"

class Score : public Subject
{
    int boardNumber;
    int level;
    int currentScore;
    int highScore;

public:
    // Constructors
    Score(int level, int boardNumber);
    // Setters
    void updateScoreRow();
    void updateScoreBlock(int blockLevel);
    void changeLevel(int level);
    void resetScore();
    // Getters
    std::string getLevel();
    std::string getScore();
    std::string getHighScore();
    int getBoardNumber();

    // Notify observers
    void drawDisplays() override;
    void drawHighScore();
};

#endif