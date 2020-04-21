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
#include "heavyplayer.h"
#include "heavylevel.h"

////////////////////////////// CONSTRUCTORS //////////////////////////////

PlayerManager::PlayerManager(std::shared_ptr<Score> score, std::shared_ptr<MainBoard> mainBoard,
                             std::shared_ptr<Level> level, std::shared_ptr<NextBlockBoard> nextBlockBoard,
                             std::shared_ptr<HoldBlockBoard> holdBlockBoard,
                             std::shared_ptr<Message> message) : level{level}, message{message}, isPlaying{false}
{
    this->player = std::make_shared<Player>(score, mainBoard, nextBlockBoard, holdBlockBoard, level->getLevelNumber());
}

////////////////////////////// SETTERS //////////////////////////////

void PlayerManager::setOpponent(std::shared_ptr<PlayerManager> opponentManager)
{
    this->opponentManager = opponentManager;
}

void PlayerManager::setIsPlaying()
{
    this->isPlaying = true;
    message->playing();
}

void PlayerManager::setRandom(bool random)
{
    this->level->setRandom(random);
}

void PlayerManager::changeLevel(int num)
{
    int levelNumber = level->getLevelNumber() + num;

    if (levelNumber < 0)
        levelNumber = 0;
    if (levelNumber > 4)
        levelNumber = 4;

    player->setLevel(num + level->getLevelNumber());

    // assuming num is +-1, undecorate if current Level >= 3
    if (level->getLevelNumber() >= 3 && levelNumber < level->getLevelNumber())
        setPlayer(player->getPlayer());
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
        // set heavy decorator
        setPlayer(std::make_shared<HeavyLevel>(getPlayer()));
        break;
    case 4:
        level = std::make_shared<Level4>(sequence);
        // should already have heavy, since coming from Level 3
        // TODO: turn Level4Effect into decorator and add here
        break;
    }
}

void PlayerManager::setLevel(std::shared_ptr<Level> level)
{
    this->level = level;
}

void PlayerManager::setPlayer(std::shared_ptr<Player> player)
{
    this->player = player;
}

////////////////////////////// GETTERS //////////////////////////////

int PlayerManager::getLevel() { return this->level->getLevelNumber(); }

bool PlayerManager::getIsLost()
{
    bool isLost = player->getIsLost();

    if (isLost)
        getOpponent()->getMessage()->playerWon();
    return isLost;
}

bool PlayerManager::getIsPlaying()
{
    if (!isPlaying)
        message->clearMessage();
    return isPlaying;
}

std::shared_ptr<Player> PlayerManager::getPlayer() { return player; }

std::shared_ptr<PlayerManager> PlayerManager::getOpponent()
{
    return opponentManager.lock();
}

std::shared_ptr<Message> PlayerManager::getMessage() { return message; }

////////////////////////////// BLOCK FUNCTIONS //////////////////////////////

void PlayerManager::initBlocks()
{
    player->setCurrentBlock(level->createBlock());
    player->setNextBlock(level->createBlock());
}

void PlayerManager::setNextBlock()
{
    player->setNextBlock(level->createBlock());
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
    player->getMainBoard()->removeBlock();
    // player->getCurrentBlock()->drawBlock(Xwindow::White);
    player->setCurrentBlock(block);
}

bool PlayerManager::moveBlock(char direction, int magnitude)
{
    bool checkMove = player->moveBlock(direction, magnitude);
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
        if (player->getIsDecorated()) // if decorated by player, remove decorator
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

////////////////////////////// SPECIAL ACTIONS //////////////////////////////

bool PlayerManager::getCanSpecial()
{
    bool canSpecial = player->getCanSpecial();
    if (canSpecial)
        message->specialReady();
    return canSpecial;
}

void PlayerManager::forceOpponentBlock(char blockType)
{
    if (player->getCanSpecial())
    {
        getOpponent()->forceBlock(blockType);
        isPlaying = false;
        player->toggleCanSpecial();
    }
}

void PlayerManager::blind()
{
    if (player->getCanSpecial())
    {
        getOpponent()->getPlayer()->toggleBlind();
        isPlaying = false;
        player->toggleCanSpecial();
    }
}

void PlayerManager::makeHeavy()
{
    if (player->getCanSpecial())
    {
        getOpponent()->setPlayer(
            std::make_shared<HeavyPlayer>(getOpponent()->getPlayer()));
        isPlaying = false;
        player->toggleCanSpecial();
    }
}