#include "score.h"
#include "../display/window.h"
#include "../display/view.h"

Score::Score(int level, std::shared_ptr<Board> board) : Subject{board},  level{level}, currentScore{0}, highScore{0} {}

void Score::updateScoreRow()
{
    this->currentScore += level * level;
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
    drawDisplays();
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
