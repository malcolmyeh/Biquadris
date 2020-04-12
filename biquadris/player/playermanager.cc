#include "playermanager.h"
#include "player.h"
#include "../level/level0.h"
#include "../level/level1.h"
#include "../level/level2.h"
#include "../level/level3.h"
#include "../level/level4.h"
#include "../block/dblock.h"
#include "../block/iblock.h"
#include "../block/jblock.h"
#include "../block/lblock.h"
#include "../block/oblock.h"
#include "../block/sblock.h"
#include "../block/tblock.h"
#include "../block/zblock.h"

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

void PlayerManager::initBlocks()
{
    player->setCurrentBlock(level->createBlock());
    player->setNextBlock(level->createBlock());
}

void PlayerManager::setNextBlock()
{
    player->setNextBlock(level->createBlock());
}

void PlayerManager::changeLevel(int level)
{
    std::string file = this->level->getFile();

    player->setLevel(level);
}

void PlayerManager::forceBlock(char blockType)
{
    std::shared_ptr<Block> block;
    switch (blockType)
    {
    case 'I':
        block = std::make_shared<IBlock>(level->getLevelNumber());
        break;
    case 'J':
        block = std::make_shared<JBlock>(level->getLevelNumber());
        break;
    case 'L':
        block = std::make_shared<LBlock>(level->getLevelNumber());
        break;
    case 'O':
        block = std::make_shared<OBlock>(level->getLevelNumber());
        break;
    case 'S':
        block = std::make_shared<SBlock>(level->getLevelNumber());
        break;
    case 'Z':
        block = std::make_shared<ZBlock>(level->getLevelNumber());
        break;
    case 'T':
        block = std::make_shared<TBlock>(level->getLevelNumber());
        break;
    }
    opponent->setCurrentBlock(block);
}

bool PlayerManager::getCanSpecial()
{
    return player->getCanSpecial();
}

bool PlayerManager::moveBlock(char direction)
{
    return player->moveBlock(direction);
}

bool PlayerManager::rotateBlock(std::string direction)
{
    return player->rotateBlock(direction);
}

void PlayerManager::dropBlock()
{
    player->dropBlock();
}

std::shared_ptr<Player> PlayerManager::getPlayer()
{
    return player;
}