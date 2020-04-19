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
      holdBlockBoard{holdBlockBoard}, canSpecial{false}, rowCleared{false},
      blocksDropped{0}, isBlind{false}, isLost{false}, isDecorated{false}
{
}

Player::Player(Player *other)
{
    score = other->score;
    mainBoard = other->mainBoard;
    nextBlockBoard = other->nextBlockBoard;
    holdBlockBoard = other->holdBlockBoard;
    canSpecial = other->canSpecial;
    isBlind = other->isBlind;
    isLost = other->isLost;
    isDecorated = other->isDecorated;
    rowCleared = other->rowCleared;
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
    if (hasHoldBlock())
    {
        std::shared_ptr<Block> oldHoldBlock = holdBlock;
        std::shared_ptr<Block> oldCurrentBlock = currentBlock;
        mainBoard->removeBlock();
        currentBlock->setHoldBlockBoard(holdBlockBoard); // erases current from main, draws in hold
        holdBlockBoard->setBlock(currentBlock);
        this->holdBlock = this->currentBlock;
        setCurrentBlock(oldHoldBlock);                          // erases hold, draws in main, but erases new hold block too
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
    if (rowsCleared > 0)
        rowCleared = true;
}

bool Player::getRowCleared()
{
    bool temp = rowCleared;
    rowCleared = false; // this will be checked only once per drop
    return temp;
}

bool Player::currentPlaced()
{
    if (currentBlock->isPlaced() || currentBlock->isEmpty())
    {
        ++blocksDropped;
        level4Effect();
        setCurrentBlock(nextBlock);
        return true;
    }
    return false;
}

// Level 4: If 5 blocks have been dropped without clearing at least one row,
// create and drop a Dot Block
void Player::level4Effect()
{
    if (level == 4)
    {
        if (getRowCleared() && blocksDropped % 5 == 0)
        {
            std::shared_ptr<DBlock> dot = std::make_shared<DBlock>(4);
            isLost = dot->setMainBoard(mainBoard);
            mainBoard->addBlock(dot);
            dot->drop();
        }
    }
}

void Player::setLevel(int level)
{
    this->level = level;
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
