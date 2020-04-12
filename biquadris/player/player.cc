#include "player.h"
#include "../block/block.h"
#include "../score/score.h"
#include "../board/board.h"
#include "../display/window.h"

Player::Player(std::shared_ptr<Board> board, std::shared_ptr<Score> score)
    : board{board}, score{score}, canSpecial{false} {}

std::shared_ptr<Block> Player::generateBlock(char blockType)
{
    switch (blockType)
    {
    case 'I':
        return Block::makeBlock(Xwindow::Cyan, board, level);
    case 'J':
        return Block::makeBlock(Xwindow::Blue, board, level);
    case 'L':
        return Block::makeBlock(Xwindow::Orange, board, level);
    case 'O':
        return Block::makeBlock(Xwindow::Yellow, board, level);
    case 'S':
        return Block::makeBlock(Xwindow::Green, board, level);
    case 'Z':
        return Block::makeBlock(Xwindow::Red, board, level);
    case 'T':
        return Block::makeBlock(Xwindow::Magenta, board, level);
    }
}

void Player::setCurrentBlock(char blockType){
    currentBlock = generateBlock(blockType);
}

void Player::setNextBlock(char blockType){
    nextBlock = generateBlock(blockType);
}

void Player::initBlocks(char blockType1, char blockType2){
    setCurrentBlock(blockType1);
    setNextBlock(blockType2);
}
bool Player::moveBlock(char direction)
{
    currentBlock->move(direction);
    if (direction == 'D')
        checkRow();
}

bool Player::rotateBlock(std::string direction)
{
    currentBlock->rotate(direction);
}

void Player::dropBlock()
{
    currentBlock->drop();
    checkRow();
    if (isBlind) toggleBlind();
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
    board->toggleBlind();
    isBlind = !isBlind;
}

void Player::checkRow()
{
    if (board->checkRow(score) > 2)
        canSpecial = true;
}

// lets PlayersManager know when currentBlock is placed and to call setBlock
bool Player::currentPlaced()
{
    if (currentBlock->isPlaced())
    {
        currentBlock = nextBlock;
        return true;
    }
    return false;
}

void Player::setLevel(int level)
{
    this->level = level;
}