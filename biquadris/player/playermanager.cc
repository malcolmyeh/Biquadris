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

PlayerManager::PlayerManager(std::shared_ptr<Score> score, std::shared_ptr<MainBoard> mainBoard,
 std::shared_ptr<Level> level, std::shared_ptr<NextBlockBoard> nextBlockBoard)
{
    this->player = std::make_shared<Player>(score, mainBoard, nextBlockBoard);
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

void PlayerManager::setLevel(std::shared_ptr<Level> level)
{
    this->level = level;
    player->setLevel(level->getLevelNumber());
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
    bool checkMove = player->moveBlock(direction);
    if (player->currentPlaced() && !player->getIsLost())
    {
        setNextBlock();
    }

    return checkMove;
}

bool PlayerManager::rotateBlock(std::string direction)
{
    return player->rotateBlock(direction);
}

void PlayerManager::dropBlock()
{
    player->dropBlock();
    if (player->currentPlaced() && !player->getIsLost())
    {
        setNextBlock();
    }
}

std::shared_ptr<Player> PlayerManager::getPlayer()
{
    return player;
}