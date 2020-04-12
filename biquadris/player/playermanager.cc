#include "playermanager.h"
#include "player.h"
#include "level.h"

PlayerManager::PlayerManager(std::shared_ptr<Score> score, std::shared_ptr<Board> board, std::shared_ptr<Level> level)
{
    this->player = std::make_shared<Player>(board, score);
    this->level = level;
    player->setLevel(level->getLevelNumber());
}

void PlayerManager::setOpponent(std::shared_ptr<Player> opponent)
{
    this->opponent = opponent;
}

void PlayerManager::initBlocks(){
    player->initBlocks(level->getBlockType(), level->getBlockType());
}

void PlayerManager::changeLevel(int level)
{
    this->level = Level::makeLevel(level);
    player->setLevel(level);
}

void PlayerManager::forceBlock(char blockType)
{
    opponent->setCurrentBlock(blockType);
}

bool PlayerManager::getCanSpecial()
{
    return player->getCanSpecial();
}

void PlayerManager::setNextBlock()
{
    player->setNextBlock(level->getBlockType());
}

bool PlayerManager::moveBlock(char direction)
{
    player->moveBlock(direction);
}

bool PlayerManager::rotateBlock(std::string direction)
{
    player->rotateBlock(direction);
}

void PlayerManager::dropBlock()
{
    player->dropBlock();
}

std::shared_ptr<Player> PlayerManager::getPlayer(){
    return player;
}