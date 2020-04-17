#include "player.h"
#include "../block/dblock.h"
#include "../block/iblock.h"
#include "../block/jblock.h"
#include "../block/lblock.h"
#include "../block/oblock.h"
#include "../block/sblock.h"
#include "../block/tblock.h"
#include "../block/zblock.h"
#include "../score/score.h"
#include "../board/mainboard.h"
#include "../board/nextblockboard.h"
#include "../display/window.h"

Player::Player(std::shared_ptr<Score> score, std::shared_ptr<MainBoard> mainBoard,
               std::shared_ptr<NextBlockBoard> nextBlockBoard,
               std::shared_ptr<HoldBlockBoard> holdBlockBoard)
    : score{score}, mainBoard{mainBoard}, nextBlockBoard{nextBlockBoard},
      holdBlockBoard{holdBlockBoard}, canSpecial{false},
      isBlind{false}, isLost{false}, isDecorated{false}
{
}

Player::Player(std::shared_ptr<Player> other)
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

bool Player::moveBlock(char direction)
{
    bool checkMove = currentBlock->move(direction);
    if (direction == 'D')
    {
        checkRow();
    }
    return checkMove;
}

bool Player::rotateBlock(std::string direction)
{
    return currentBlock->rotate(direction);
}

void Player::dropBlock()
{
    currentBlock->drop();
    checkRow();
    if (isBlind)
        toggleBlind();
}

bool Player::hasHoldBlock()
{
    if (this->holdBlock)
        return true;
    return false;
}

void Player::setHoldBlock()
{
    currentBlock->setHoldBlockBoard(holdBlockBoard);
    if (hasHoldBlock())
        this->currentBlock.swap(this->holdBlock);
    else
    {
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
    if (mainBoard->checkRow(score) > 2)
        canSpecial = true;
}

bool Player::currentPlaced()
{
    if (currentBlock->isPlaced() || currentBlock->isEmpty())
    {
        setCurrentBlock(nextBlock);
        return true;
    }
    return false;
}

void Player::setLevel(int level)
{
    this->level = level;
}

std::shared_ptr<Board> Player::getMainBoard()
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