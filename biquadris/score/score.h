#ifndef SCORE_H
#define SCORE_H

#include "../subject/subject.h"

class Score : public Subject
{
    int level;
    int currentScore;
    int highScore;

public:
    Score(int level, std::shared_ptr<Board> board);
    void updateScoreRow();
    void updateScoreBlock(int level);
    void changeLevel(int level);
    void resetScore();
    void drawDisplays() override;
    std::string getLevel();
    std::string getScore();
};

#endif