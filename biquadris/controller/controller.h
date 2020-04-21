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
#include "../display/cursesdisplay.h"
#include "../board/mainboard.h"
#include "../board/nextblockboard.h"
#include "../board/holdblockboard.h"
#include "../player/playermanager.h"
#include "../score/score.h"
#include "../message/message.h"
#include "../block/block.h"
#include "../level/level0.h"
#include "../level/level1.h"
#include "../level/level2.h"
#include "../level/level3.h"
#include "../level/level4.h"

class PlayerManager;

class Controller
{
    std::vector<std::shared_ptr<PlayerManager>> playerManagers;
    std::shared_ptr<PlayerManager> currentPlayer;
    std::vector<std::vector<std::shared_ptr<View>>> displays;
    std::vector<std::shared_ptr<MainBoard>> mainBoards;
    std::vector<std::shared_ptr<NextBlockBoard>> nextBlockBoards;
    std::vector<std::shared_ptr<HoldBlockBoard>> holdBlockBoards;
    std::vector<std::shared_ptr<Score>> scores;
    std::vector<std::shared_ptr<Message>> messages;

    void makeDisplays(bool graphics, bool curses);
    void makeBoards();
    void makePlayerManagers(int startLevel, std::vector<std::string> scriptFiles);
    void makeScores(int startLevel);
    void makeMessages();
    void initBoards();
    void restart();
    void changeTurn();
    std::shared_ptr<Level> createLevel(int levelNumber, std::string file);

public:
    Controller(bool graphics, bool curses, std::vector<std::string> scriptFiles,
               int startLevel);
    void runGame();
    void gameEnd();
};

#endif