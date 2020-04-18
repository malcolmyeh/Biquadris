#ifndef PLAYERMANAGER_H
#define PLAYERMANAGER_H

#include "player.h"

class Player;
class Level;
class Score;
class MainBoard;
class NextBlockBoard;
class HoldBlockBoard;
class Message;

class PlayerManager
{
    std::shared_ptr<Player> player;
    std::shared_ptr<Player> opponent;
    std::shared_ptr<Level> level;
    std::shared_ptr<Message> message;

    bool getCanSpecial();

public:
    PlayerManager(std::shared_ptr<Score> score, std::shared_ptr<MainBoard> mainBoard,
                  std::shared_ptr<Level> level, std::shared_ptr<NextBlockBoard> nextBlockBoard,
                  std::shared_ptr<HoldBlockBoard> holdBlockBoard,
                  std::shared_ptr<Message> message);
    void setOpponent(std::shared_ptr<PlayerManager> opponentManager);
    bool getOpponentLost();
    void initBlocks();
    void forceBlock(char blockType);
    void blind();
    void makeHeavy();
    void setNextBlock();
    bool moveBlock(char direction);
    bool rotateBlock(std::string direction);
    void dropBlock();
    void holdBlock();
    void changeLevel(int num);
    void setRandom(bool random);
    std::shared_ptr<Player> getPlayer();
    int getLevel();
};

#endif