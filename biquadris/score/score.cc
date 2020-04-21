#include "score.h"
#include "../display/window.h"
#include "../display/view.h"

////////////////////////////// CONSTRUCTOR //////////////////////////////

Score::Score(int level, int boardNumber)
    : boardNumber{boardNumber}, level{level}, currentScore{0}, highScore{0} {}

////////////////////////////// SETTERS //////////////////////////////

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

////////////////////////////// GETTERS //////////////////////////////

std::string Score::getLevel() { return std::to_string(level); }
std::string Score::getScore() { return std::to_string(currentScore); }
std::string Score::getHighScore() { return std::to_string(highScore); }
int Score::getBoardNumber() { return boardNumber; }

////////////////////////////// NOTIFY OBSERVERS //////////////////////////////

void Score::drawDisplays()
{
    for (auto &display : displays)
        display.lock()->drawScore(*this);
}
