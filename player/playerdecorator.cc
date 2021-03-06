#include "playerdecorator.h"
#include "../board/mainboard.h"
#include "../board/holdblockboard.h"
#include "../board/nextblockboard.h"
#include "../block/block.h"

////////////////////////////// CONSTRUCTORS //////////////////////////////

PlayerDecorator::PlayerDecorator(std::shared_ptr<Player> player, bool isDecorated)
    : player{player}
{
    this->isDecorated = isDecorated;
}

////////////////////////////// SETTERS //////////////////////////////

void PlayerDecorator::setCurrentBlock(std::shared_ptr<Block> block)
{
    player->setCurrentBlock(block);
}

void PlayerDecorator::setNextBlock(std::shared_ptr<Block> block)
{
    player->setNextBlock(block);
}

void PlayerDecorator::setHoldBlock() { player->setHoldBlock(); }

void PlayerDecorator::setLevel(int level) { player->setLevel(level); }

void PlayerDecorator::toggleCanSpecial() { player->toggleCanSpecial(); }

void PlayerDecorator::toggleBlind() { player->toggleBlind(); }

////////////////////////////// GETTERS //////////////////////////////

bool PlayerDecorator::hasHoldBlock() { return player->hasHoldBlock(); }

bool PlayerDecorator::getCanSpecial() { return player->getCanSpecial(); }

bool PlayerDecorator::getIsLost() { return player->getIsLost(); }

bool PlayerDecorator::getIsDecorated() { return isDecorated; }

bool PlayerDecorator::getRowCleared() { return player->getRowCleared(); }

std::shared_ptr<Block> PlayerDecorator::getCurrentBlock()
{
    return player->getCurrentBlock();
}

std::shared_ptr<Block> PlayerDecorator::getNextBlock() { return player->getNextBlock(); }

std::shared_ptr<Block> PlayerDecorator::getHoldBlock() { return player->getHoldBlock(); }

std::shared_ptr<MainBoard> PlayerDecorator::getMainBoard()
{
    return player->getMainBoard();
}

std::shared_ptr<NextBlockBoard> PlayerDecorator::getNextBlockBoard()
{
    return player->getNextBlockBoard();
}

std::shared_ptr<HoldBlockBoard> PlayerDecorator::getHoldBlockBoard()
{
    return player->getHoldBlockBoard();
}

std::shared_ptr<Score> PlayerDecorator::getScore() { return player->getScore(); }

std::shared_ptr<Player> PlayerDecorator::getPlayer() { return player; }

int PlayerDecorator::getLevel() { return player->getLevel(); }

////////////////////////////// BLOCK FUNCTIONS //////////////////////////////

void PlayerDecorator::dropBlock() { player->dropBlock(); }

bool PlayerDecorator::moveBlock(char direction, int magnitude)
{
    return player->moveBlock(direction, magnitude);
}

bool PlayerDecorator::rotateBlock(std::string direction)
{
    return player->rotateBlock(direction);
}

void PlayerDecorator::checkRow() { player->checkRow(); }

bool PlayerDecorator::currentPlaced() { return player->currentPlaced(); }

void PlayerDecorator::level4Effect() { player->level4Effect(); }
