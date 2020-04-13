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
#include "../board/board.h"
#include "../display/window.h"

Player::Player(std::shared_ptr<Score> score, std::shared_ptr<Board> board)
    : score{score}, board{board}, canSpecial{false}
{
}

void Player::setCurrentBlock(std::shared_ptr<Block> block)
{
    currentBlock = block;
    block->setBoard(board);
    board->addBlock(block);
}

void Player::setNextBlock(std::shared_ptr<Block> block)
{
    nextBlock = block;
}

bool Player::moveBlock(char direction)
{
    if (!currentBlock){
        std::cout << "NO BLOCK THIS SHOULDN'T HAPPEN" << std::endl;
        return false;
    }
    std::cout << "Player::moveBlock" << std::endl;
    bool checkMove = currentBlock->move(direction);
    if (direction == 'D')
    {
        std::cout << "direction is DOWN, checking row..." << std::endl;
        checkRow();
    }
    return checkMove;
}

bool Player::rotateBlock(std::string direction)
{
    std::cout << "Player::roateBlock" << std::endl;
    return currentBlock->rotate(direction);
}

void Player::dropBlock()
{
    std::cout << "Player::moveBlock" << std::endl;
    currentBlock->drop();
    std::cout << "Block is at lowest possible Y, checking row..." << std::endl;
    checkRow();
    if (isBlind)
        toggleBlind();
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
    std::cout << "Player::checkRow" << std::endl;
    if (board->checkRow(score) > 2)
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

std::shared_ptr<Board> Player::getBoard()
{
    return board;
}