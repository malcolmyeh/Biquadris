#include "playerdecorator.h"
#include "../board/mainboard.h"
#include "../board/holdblockboard.h"
#include "../board/nextblockboard.h"
#include "../block/block.h"
PlayerDecorator::PlayerDecorator(std::shared_ptr<Player> player, bool isDecorated)
    : player{player}
{
    this->isDecorated = isDecorated;
}

std::shared_ptr<Block> PlayerDecorator::getCurrentBlock()
{
    return player->getCurrentBlock();
}

std::shared_ptr<Block> PlayerDecorator::getNextBlock()
{
    return player->getNextBlock();
}
std::shared_ptr<Block> PlayerDecorator::getHoldBlock()
{
    return player->getHoldBlock();
}

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

std::shared_ptr<Score> PlayerDecorator::getScore()
{
    return player->getScore();
}
void PlayerDecorator::setCurrentBlock(std::shared_ptr<Block> block)
{
    player->setCurrentBlock(block);
}
void PlayerDecorator::setNextBlock(std::shared_ptr<Block> block)
{
    player->setNextBlock(block);
}
void PlayerDecorator::setHoldBlock()
{
    if (hasHold)
    {
        std::cout << "HAS HOLD BLOCK" << std::endl;
        std::shared_ptr<Block> oldHoldBlock = getHoldBlock();
        std::shared_ptr<Block> oldCurrentBlock = getCurrentBlock();
        getMainBoard()->removeBlock();
        getCurrentBlock()->setHoldBlockBoard(getHoldBlockBoard()); // erases current from main, draws in hold
        getHoldBlockBoard()->setBlock(getCurrentBlock());
        getHoldBlock() = getCurrentBlock();
        setCurrentBlock(oldHoldBlock);                            // erases hold, draws in main, but erases new hold block too
        oldCurrentBlock->drawBlock(oldCurrentBlock->getColour()); // redraw erased hold block cells
    }
    else
    {
        std::cout << "NO HOLD BLOCK " << std::endl;
        getMainBoard()->removeBlock();
        getCurrentBlock()->setHoldBlockBoard(getHoldBlockBoard());
        getHoldBlockBoard()->setBlock(getCurrentBlock());
        getHoldBlock() = getCurrentBlock();
        setCurrentBlock(getNextBlock());
        hasHold = true;
    }
}

void PlayerDecorator::dropBlock()
{
    player->dropBlock();
}
