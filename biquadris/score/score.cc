#include "score.h"
#include "../display/window.h"
#include "../display/view.h"

Score::Score(int level, int boardNumber) : level{level}, boardNumber{boardNumber}, currentScore{0}, highScore{0} {}

void Score::updateScoreRow(int linesCleared)
{
    this->currentScore += (level + linesCleared) * (level + linesCleared);
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
    this->level = level;
    drawDisplays();
}
void Score::resetScore()
{
    currentScore = 0;
    // need to draw?
}

void Score::drawDisplays()
{
    for (auto &display : displays)
        display->drawScore(*this);
}

std::string Score::getLevel()
{
    return std::to_string(level);
}
std::string Score::getScore()
{
    return std::to_string(currentScore);
}

int Score::getBoardNumber()
{
    return boardNumber;
}