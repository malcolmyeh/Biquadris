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

Player::Player(std::shared_ptr<Board> board, std::shared_ptr<Score> score)
    : score{score}, board{board}, canSpecial{false} {}

void Player::setCurrentBlock(std::shared_ptr<Block> block){
    currentBlock = block;
    block->setBoard(board);
}

void Player::setNextBlock(std::shared_ptr<Block> block){
    nextBlock = block;
    block->setBoard(board);
}

bool Player::moveBlock(char direction)
{
    bool checkMove = currentBlock->move(direction);
    if (direction == 'D')
        checkRow();
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

std::shared_ptr<Board> Player::getBoard(){
    return board;
}