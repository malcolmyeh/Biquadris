#ifndef PLAYERDECORATOR_H
#define PLAYERDECORATOR_H

#include "player.h"

class PlayerDecorator : public Player
{
protected:
    std::shared_ptr<Player> player;

public:
    PlayerDecorator(std::shared_ptr<Player> player,  bool isDecorated);
    void undecorate();
};

#endif