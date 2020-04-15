#ifndef PLAYERMANAGER_H
#define PLAYERMANAGER_H

#include "player.h"

class Player;
class Level;
class Score;

class Board;
class MainBoard;
class NextBlockBoard;

class PlayerManager
{
    std::shared_ptr<Player> player;
    std::shared_ptr<Player> opponent;
    std::shared_ptr<Level> level;

    bool getCanSpecial();

public:
    PlayerManager(std::shared_ptr<Score> score, std::shared_ptr<MainBoard> mainBoard,
                  std::shared_ptr<Level> level, std::shared_ptr<NextBlockBoard> nextBlockBoard);
    void setOpponent(std::shared_ptr<Player> opponent);
    void initBlocks();
    void forceBlock(char blockType);
    void blind();
    void setNextBlock();
    bool moveBlock(char direction);
    bool rotateBlock(std::string direction);
    void dropBlock();
    void setLevel(std::shared_ptr<Level> level);
    std::shared_ptr<Player> getPlayer();
};

#endif