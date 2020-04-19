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
    std::shared_ptr<PlayerManager> opponentManager;
    std::shared_ptr<Level> level;
    std::shared_ptr<Message> message;
    bool isPlaying = false;
    bool getCanSpecial();

public:
    PlayerManager(std::shared_ptr<Score> score, std::shared_ptr<MainBoard> mainBoard,
                  std::shared_ptr<Level> level, std::shared_ptr<NextBlockBoard> nextBlockBoard,
                  std::shared_ptr<HoldBlockBoard> holdBlockBoard,
                  std::shared_ptr<Message> message);

    // Setters
    void setOpponent(std::shared_ptr<PlayerManager> opponentManager);
    void setIsPlaying();
    void setRandom(bool random);
    void changeLevel(int num);

    // Getters
    bool getIsLost();
    int getLevel();
    bool getIsPlaying();
    std::shared_ptr<Player> getPlayer();

    // Block functions
    void initBlocks();
    void setNextBlock();
    void forceBlock(char blockType);
    bool moveBlock(char direction);
    bool rotateBlock(std::string direction);
    void dropBlock();
    void holdBlock();

    // Special Actions
    void forceOpponentBlock(char blockType);
    void blind();
    void makeHeavy();
};

#endif