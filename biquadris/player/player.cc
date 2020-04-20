#include "player.h"
#include "../block/dblock.h"
#include "../score/score.h"
#include "../board/mainboard.h"
#include "../board/nextblockboard.h"
#include "../display/window.h"

Player::Player(std::shared_ptr<Score> score, std::shared_ptr<MainBoard> mainBoard,
               std::shared_ptr<NextBlockBoard> nextBlockBoard,
               std::shared_ptr<HoldBlockBoard> holdBlockBoard)
    : score{score}, mainBoard{mainBoard}, nextBlockBoard{nextBlockBoard},
      holdBlockBoard{holdBlockBoard}, canSpecial{false}, isBlind{false}, isLost{false}, isDecorated{false}
{
}

Player::Player(std::shared_ptr<Player> player)
{
    this->currentBlock = player->currentBlock;
    this->nextBlock = player->nextBlock;
    this->holdBlock = player->holdBlock;
    this->score = player->score;
    this->mainBoard = player->mainBoard;
    this->nextBlockBoard = player->nextBlockBoard;
    this->holdBlockBoard = player->holdBlockBoard;
    this->canSpecial = player->canSpecial;
    this->level = player->level;
    this->isBlind = player->isBlind;
    this->isLost = player->isLost;
    this->isDecorated = player->isDecorated;
}

Player::Player(Player *other) // fix
{
    score = other->score;
    mainBoard = other->mainBoard;
    nextBlockBoard = other->nextBlockBoard;
    holdBlockBoard = other->holdBlockBoard;
    canSpecial = other->canSpecial;
    isBlind = other->isBlind;
    isLost = other->isLost;
    isDecorated = other->isDecorated;
}

Player::Player() {}

void Player::setCurrentBlock(std::shared_ptr<Block> block)
{
    currentBlock = block;
    isLost = !currentBlock->setMainBoard(mainBoard);
    mainBoard->addBlock(currentBlock);
}

void Player::setNextBlock(std::shared_ptr<Block> block)
{
    nextBlock = block;
    nextBlock->setNextBlockBoard(nextBlockBoard);
}

bool Player::moveBlock(char direction, int magnitude)
{
    bool checkMove = getCurrentBlock()->move(direction, magnitude);
    if (direction == 'D')
    {
        checkRow();
    }
    return checkMove;
}

bool Player::rotateBlock(std::string direction)
{
    return getCurrentBlock()->rotate(direction);
}

void Player::dropBlock()
{
    getCurrentBlock()->drop();
    checkRow();
    if (isBlind)
        toggleBlind();
}

bool Player::hasHoldBlock()
{

    std::cout << "Player::hasHoldBlock" << std::endl;
    if (this->holdBlock)
    {
        std::cout << "player has hold";
        return true;
    }

    return false;
}

void Player::setHoldBlock()
{
    if (hasHoldBlock())
    {
        std::shared_ptr<Block> oldHoldBlock = holdBlock;
        std::shared_ptr<Block> oldCurrentBlock = currentBlock;
        mainBoard->removeBlock();
        currentBlock->setHoldBlockBoard(holdBlockBoard); // erases current from main, draws in hold
        holdBlockBoard->setBlock(currentBlock);
        this->holdBlock = this->currentBlock;
        setCurrentBlock(oldHoldBlock);                            // erases hold, draws in main, but erases new hold block too
        oldCurrentBlock->drawBlock(oldCurrentBlock->getColour()); // redraw erased hold block cells
    }
    else
    {
        mainBoard->removeBlock();
        currentBlock->setHoldBlockBoard(holdBlockBoard);
        holdBlockBoard->setBlock(currentBlock);
        this->holdBlock = this->currentBlock;
        setCurrentBlock(nextBlock);
    }
}

bool Player::getCanSpecial()
{
    return canSpecial;
}

void Player::toggleCanSpecial()
{
    canSpecial = !canSpecial;
}

void Player::toggleBlind()
{
    mainBoard->toggleBlind();
    isBlind = !isBlind;
}

void Player::checkRow()
{
    int rowsCleared = mainBoard->checkRow(score);
    if (rowsCleared >= 2)
        canSpecial = true;
}

bool Player::currentPlaced()
{
    if (getCurrentBlock()->isPlaced() || getCurrentBlock()->isEmpty())
    {
        setCurrentBlock(getNextBlock());
        return true;
    }
    return false;
}

void Player::setLevel(int level)
{
    this->level = level;
    score->changeLevel(level);
}

std::shared_ptr<MainBoard> Player::getMainBoard()
{
    return mainBoard;
}

bool Player::getIsLost()
{
    return isLost;
}

bool Player::getIsDecorated()
{
    return isDecorated;
}

std::shared_ptr<Player> Player::getPlayer()
{
    return std::make_shared<Player>(this);
}

std::shared_ptr<Block> Player::getCurrentBlock()
{
    return currentBlock;
}

std::shared_ptr<Block> Player::getNextBlock()
{
    return nextBlock;
}
std::shared_ptr<Block> Player::getHoldBlock()
{
    return holdBlock;
}

std::shared_ptr<NextBlockBoard> Player::getNextBlockBoard()
{
    return nextBlockBoard;
}
std::shared_ptr<HoldBlockBoard> Player::getHoldBlockBoard()
{
    return holdBlockBoard;
}

std::shared_ptr<Score> Player::getScore()
{
    return score;
}