#include "player.h"
#include "../block/dblock.h"
#include "../score/score.h"
#include "../board/mainboard.h"
#include "../board/nextblockboard.h"
#include "../display/window.h"


Player::Player(std::shared_ptr<Score> score, std::shared_ptr<MainBoard> mainBoard,
               std::shared_ptr<NextBlockBoard> nextBlockBoard,
               std::shared_ptr<HoldBlockBoard> holdBlockBoard, int level)
    : score{score}, mainBoard{mainBoard}, nextBlockBoard{nextBlockBoard},
      holdBlockBoard{holdBlockBoard}, canSpecial{false}, level{level}, rowCleared{false},
      blocksDropped{0}, isBlind{false}, isLost{false}, isDecorated{false} {}

Player::Player(Player *player)
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
    this->rowCleared = player->rowCleared;
    this->isBlind = player->isBlind;
    this->isLost = player->isLost;
    this->isDecorated = player->isDecorated;
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
    this->rowCleared = player->rowCleared;
    this->isBlind = player->isBlind;
    this->isLost = player->isLost;
    this->isDecorated = player->isDecorated;
}

Player::Player() {}

void Player::setCurrentBlock(std::shared_ptr<Block> block)
{
    currentBlock = block;
    // checks if block is valid - not overlapping existing block
    isLost = !currentBlock->setMainBoard(mainBoard);
    mainBoard->addBlock(currentBlock);
}

void Player::setNextBlock(std::shared_ptr<Block> block)
{
    nextBlock = block;
    nextBlock->setNextBlockBoard(nextBlockBoard);
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

void Player::setLevel(int level)
{
    this->level = level;
    score->changeLevel(level);
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

bool Player::hasHoldBlock()
{

    if (this->holdBlock)
        return true;
    return false;
}

bool Player::getCanSpecial()
{
    return canSpecial;
}

bool Player::getIsLost()
{
    return isLost;
}

bool Player::getIsDecorated()
{
    return isDecorated;
}

bool Player::getRowCleared()
{
    bool temp = rowCleared;
    rowCleared = false; // this will be checked only once per drop
    return temp;
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

std::shared_ptr<MainBoard> Player::getMainBoard()
{
    return mainBoard;
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

int Player::getLevel()
{
    return level;
}

std::shared_ptr<Player> Player::getPlayer()
{
    return std::make_shared<Player>(this);
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

// sets canSpecial and rowCleared based on rows cleared
void Player::checkRow()
{
    int rowsCleared = mainBoard->checkRow(score);
    if (rowsCleared >= 2)
        canSpecial = true;
    if (rowsCleared > 0)
        rowCleared = true;
}

// determines if current block is placed
bool Player::currentPlaced()
{
    if (getCurrentBlock()->isPlaced() || getCurrentBlock()->isEmpty())
    {
        ++blocksDropped;
        level4Effect();
        setCurrentBlock(getNextBlock());
        return true;
    }
    return false;
}

// Level 4: If 5 blocks have been dropped without clearing at least one row,
// create and drop a Dot Block
void Player::level4Effect()
{

    if (getLevel() == 4)
    {
        if (!getRowCleared() && blocksDropped % 5 == 0)
        {
            std::shared_ptr<DBlock> dot = std::make_shared<DBlock>(4);
            isLost = dot->setMainBoard(mainBoard);
            mainBoard->addBlock(dot);
            dot->drop();
        }
    }
}
