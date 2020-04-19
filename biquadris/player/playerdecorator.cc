#include "playerdecorator.h"

PlayerDecorator::PlayerDecorator(std::shared_ptr<Player> player, bool isDecorated)
: player{player} {
    this->isDecorated = isDecorated;
}

void PlayerDecorator::undecorate(){
    return player;
}