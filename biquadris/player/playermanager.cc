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
#include "../message/message.h"
#include "heavy.h"

PlayerManager::PlayerManager(std::shared_ptr<Score> score, std::shared_ptr<MainBoard> mainBoard,
                             std::shared_ptr<Level> level, std::shared_ptr<NextBlockBoard> nextBlockBoard,
                             std::shared_ptr<HoldBlockBoard> holdBlockBoard,
                             std::shared_ptr<Message> message) : level{level}, message{message}
{
    this->player = std::make_shared<Player>(score, mainBoard, nextBlockBoard, holdBlockBoard);
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
    if (level->getLevelNumber() >= 3)
        player = std::make_shared<Heavy>(player);
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

void PlayerManager::makeHeavy()
{
    opponent = std::make_shared<Heavy>(opponent, true);
}

bool PlayerManager::getCanSpecial()
{
    bool canSpecial = player->getCanSpecial();
    if (canSpecial)
        message->specialReady();
    return canSpecial;
}

bool PlayerManager::getOpponentLost()
{
    bool opponentLost = opponent->getIsLost();
    if (opponentLost)
        message->playerWon();
    return opponentLost;
}

bool PlayerManager::moveBlock(char direction)
{
    bool checkMove = player->moveBlock(direction);
    if (player->currentPlaced() && !player->getIsLost())
    {
        setNextBlock();
        if (player->getIsDecorated())
            player = player->getPlayer();
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
        if (player->getIsDecorated())
            player = player->getPlayer();
    }
}

void PlayerManager::holdBlock()
{
    if (player->hasHoldBlock())
        player->setHoldBlock();
    else
    {
        player->setHoldBlock();
        setNextBlock();
    }
}
std::shared_ptr<Player> PlayerManager::getPlayer()
{
    return player;
}