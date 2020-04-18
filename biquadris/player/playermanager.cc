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
                             std::shared_ptr<Message> message) : level{level}, message{message}, isPlaying{false}
{
    this->player = std::make_shared<Player>(score, mainBoard, nextBlockBoard, holdBlockBoard);
    player->setLevel(level->getLevelNumber());
}

void PlayerManager::setOpponent(std::shared_ptr<PlayerManager> opponentManager)
{
    opponent = opponentManager->getPlayer();
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

void PlayerManager::changeLevel(int num)
{
    int levelNumber = level->getLevelNumber() + num;
    if (levelNumber < 0)
        levelNumber = 0;
    if (levelNumber > 4)
        levelNumber = 4;
    std::vector<char> sequence = level->getSequence();
    switch (levelNumber)
    {
    case 0:
        level = std::make_shared<Level0>(sequence);
        break;
    case 1:
        level = std::make_shared<Level1>(sequence);
        break;
    case 2:
        level = std::make_shared<Level2>(sequence);
        break;
    case 3:
        level = std::make_shared<Level3>(sequence);
        break;
    case 4:
        level = std::make_shared<Level4>(sequence);
        break;
    }
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
    isPlaying = false;
}

void PlayerManager::blind()
{
    opponent->toggleBlind();
    isPlaying = false;
}

void PlayerManager::makeHeavy()
{
    opponent = std::make_shared<Heavy>(opponent, true);
    isPlaying = false;
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
        if (!getCanSpecial()) // if no special, turn ends
            isPlaying = false;
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
        if (!getCanSpecial()) // if no special, turn ends
            isPlaying = false;
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

void PlayerManager::setRandom(bool random)
{
    this->level->setRandom(random);
}

std::shared_ptr<Player> PlayerManager::getPlayer()
{
    return player;
}

int PlayerManager::getLevel()
{
    return this->level->getLevelNumber();
}

void PlayerManager::setIsPlaying()
{
    this->isPlaying = true;
    message->playing();
}

bool PlayerManager::getIsPlaying()
{
    if (!isPlaying)
        message->clearMessage();
    return isPlaying;   
    
}