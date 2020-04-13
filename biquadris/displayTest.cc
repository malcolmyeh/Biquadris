#include "display/graphicsdisplay.h"
#include "display/textdisplay.h"
#include "board/board.h"
#include "player/playermanager.h"
#include "score/score.h"
#include "block/block.h"

#include "level/level0.h"
#include "level/level1.h"
#include "level/level2.h"
#include "level/level3.h"
#include "level/level4.h"

#include <memory>
#include <string>
#include <sstream>
#include <iostream>

int main(int argc, char *argv[])
{

    // constants
    int level = 1;
    std::string levelFile = "";

    // displays
    std::shared_ptr<TextDisplay> td = std::make_shared<TextDisplay>();
    std::shared_ptr<GraphicsDisplay> gd = std::make_shared<GraphicsDisplay>();

    // boards (+ cells)
    std::shared_ptr<Board> b1 = std::make_shared<Board>();
    std::shared_ptr<Board> b2 = std::make_shared<Board>();

    // score
    std::shared_ptr<Score> s1 = std::make_shared<Score>(level, b1);
    std::shared_ptr<Score> s2 = std::make_shared<Score>(level, b2);

    // playermanager (+ players)
    std::shared_ptr<PlayerManager> pm1 =
        std::make_shared<PlayerManager>(s1, b1, std::make_shared<Level1>(levelFile));
    std::shared_ptr<PlayerManager> pm2 =
        std::make_shared<PlayerManager>(s2, b2, std::make_shared<Level1>(levelFile));

    // link players to each other
    pm1->setOpponent(pm2->getPlayer());
    pm2->setOpponent(pm1->getPlayer());

    // put into vector for harness
    std::vector<std::shared_ptr<PlayerManager>> playerManagers;
    playerManagers.emplace_back(pm1);
    playerManagers.emplace_back(pm2);

    // link board, score, display
    b1->init(1);
    b2->init(2);
    b1->setDisplay(td);
    b1->setDisplay(gd);
    b2->setDisplay(td);
    b2->setDisplay(gd);
    s1->attach(td);
    s1->attach(gd);
    s2->attach(td);
    s2->attach(gd);

    // refresh board and score, updates display
    b1->refresh();
    b2->refresh();
    s1->drawDisplays();
    s2->drawDisplays();

    // create initial blocks
    pm1->initBlocks();
    pm2->initBlocks();

    std::cout << "                 Testing Commands: " << std::endl
              << std::endl
              << "∙ move {1,2} {L,R,D} ------- move current block " << std::endl
              << "∙ rotate {1,2} {CC, CW} ---- rotate current block" << std::endl
              << "∙ drop {1,2} --------------- drop current block" << std::endl
              << "∙ quit --------------------- exit" << std::endl;

    while (true)
    {
        std::string cmd;
        int player;
        char moveDirection;
        std::string rotateDirection;

        std::cin >> cmd;

        if (cmd == "move")
        {
            std::cin >> player;
            std::cin >> moveDirection;
            playerManagers[player - 1]->moveBlock(moveDirection);
        }
        else if (cmd == "rotate")
        {
            std::cin >> player;
            std::cin >> rotateDirection;
            playerManagers[player - 1]->rotateBlock(rotateDirection);
        }
        else if (cmd == "drop")
        {
            std::cin >> player;
            playerManagers[player - 1]->dropBlock();
        }
        else if (cmd == "quit")
        {
            break;
        }
    }
    return 0;
}