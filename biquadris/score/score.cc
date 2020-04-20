#include "score.h"
#include "../display/window.h"
#include "../display/view.h"

Score::Score(int level, int boardNumber) : boardNumber{boardNumber}, level{level}, currentScore{0}, highScore{0} {}

void Score::updateScoreRow()
{
    this->currentScore += (level + 1) * (level + 1);
    if (currentScore > highScore)
        highScore = currentScore;
    drawDisplays();
}

void Score::updateScoreBlock(int level)
{
    this->currentScore += (level + 1) * (level + 1);
    if (currentScore > highScore)
        highScore = currentScore;
    drawDisplays();
}

void Score::changeLevel(int level)
{

    if (level == 4)
    {
        this->level = 4;
    }
    else
        this->level = level;
    drawDisplays();
}
void Score::resetScore()
{
    currentScore = 0;
    drawDisplays();
}

void Score::drawDisplays()
{
    for (auto &display : displays)
        display.lock()->drawScore(*this);
}

std::string Score::getLevel()
{
    return std::to_string(level);
}
std::string Score::getScore()
{
    return std::to_string(currentScore);
}

int Score::getBoardNumber(){
    return boardNumber;
}