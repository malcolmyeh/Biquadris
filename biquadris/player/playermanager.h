#ifndef PLAYERMANAGER_H
#define PLAYERMANAGER_H

#include "player.h"

class Player;
class Level;
class Score;

class Board;

class PlayerManager
{
    std::shared_ptr<Player> player;
    std::shared_ptr<Player> opponent;
    std::shared_ptr<Level> level;

    bool getCanSpecial();

public:
    PlayerManager(std::shared_ptr<Score> score, std::shared_ptr<Board> board, std::shared_ptr<Level> level);
    void setOpponent(std::shared_ptr<Player> opponent);
    void forceBlock(char blockType);
    void blind();
    void setNextBlock();
    bool moveBlock(char direction);
    bool rotateBlock(char direction);
    void dropBlock();
    void changeLevel(int level);
};

#endif