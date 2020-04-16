#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <string>
#include <memory>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <locale>

#include "../display/graphicsdisplay.h"
#include "../display/textdisplay.h"
#include "../board/mainboard.h"
#include "../board/nextblockboard.h"
#include "../player/playermanager.h"
#include "../score/score.h"
#include "../block/block.h"
#include "../level/level0.h"
#include "../level/level1.h"
#include "../level/level2.h"
#include "../level/level3.h"
#include "../level/level4.h"

class PlayerManager;

class Controller
{
    std::vector<std::shared_ptr<PlayerManager>> playerManagers; // two element vector
    std::shared_ptr<PlayerManager> currentPlayer;
    void changeTurn();
    std::shared_ptr<Level> createLevel(int levelNumber, std::string file);

public:
    Controller(bool graphics, std::vector<std::string> scriptFiles,
               int startLevel);
    void runGame();
};

#endif