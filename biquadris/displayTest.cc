#include "display/graphicsdisplay.h"
#include "display/textdisplay.h"
#include "board/mainboard.h"
#include "board/nextblockboard.h"
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
#include <ncurses.h>

int main(int argc, char *argv[])
{

    // constants
    int level = 1;
    std::string levelFile = "";

    // displays
    std::shared_ptr<TextDisplay> td = std::make_shared<TextDisplay>();
    std::shared_ptr<GraphicsDisplay> gd = std::make_shared<GraphicsDisplay>();

    // boards (+ cells)
    std::shared_ptr<MainBoard> mb1 = std::make_shared<MainBoard>();
    std::shared_ptr<MainBoard> mb2 = std::make_shared<MainBoard>();
    std::shared_ptr<NextBlockBoard> nb1 = std::make_shared<NextBlockBoard>();
    std::shared_ptr<NextBlockBoard> nb2 = std::make_shared<NextBlockBoard>();

    // score
    std::shared_ptr<Score> s1 = std::make_shared<Score>(level, mb1);
    std::shared_ptr<Score> s2 = std::make_shared<Score>(level, mb2);

    // playermanager (+ players)
    std::shared_ptr<PlayerManager> pm1 =
        std::make_shared<PlayerManager>(s1, mb1, std::make_shared<Level2>(levelFile), nb1);
    std::shared_ptr<PlayerManager> pm2 =
        std::make_shared<PlayerManager>(s2, mb2, std::make_shared<Level2>(levelFile), nb2);

    // link players to each other
    pm1->setOpponent(pm2->getPlayer());
    pm2->setOpponent(pm1->getPlayer());

    // put into vector for harness
    std::vector<std::shared_ptr<PlayerManager>> playerManagers;
    playerManagers.emplace_back(pm1);
    playerManagers.emplace_back(pm2);

    // link board, score, display
    mb1->init(1);
    mb2->init(2);
    nb1->init(1);
    nb2->init(2);
    mb1->setDisplay(td);
    mb1->setDisplay(gd);
    mb2->setDisplay(td);
    mb2->setDisplay(gd);
    nb1->setDisplay(td);
    nb1->setDisplay(gd);
    nb2->setDisplay(td);
    nb2->setDisplay(gd);

    s1->attach(td);
    s1->attach(gd);
    s2->attach(td);
    s2->attach(gd);

    // refresh board and score, updates display
    mb1->refresh();
    mb2->refresh();
    nb1->refresh();
    nb2->refresh();
    s1->drawDisplays();
    s2->drawDisplays();

    // create initial blocks
    pm1->initBlocks();
    pm2->initBlocks();

    std::cout << "       Testing Commands:" << std::endl
              << std::endl
              << "∙ move {1,2} {L,R,D} ------- move current block " << std::endl
              << "∙ rotate {1,2} {CC, CW} ---- rotate current block" << std::endl
              << "∙ drop {1,2} --------------- drop current block" << std::endl
              << "∙ quit --------------------- exit" << std::endl
              << "       Player 1 Shortcuts:" << std::endl
              << "∙ {asd} --------------------- move" << std::endl
              << "∙ {w} ----------------------- drop" << std::endl
              << "∙ {eq} ---------------------- rotate" << std::endl
              << "       Player 2 Shortcuts:" << std::endl
              << "∙ {jkl} --------------------- move" << std::endl
              << "∙ {i} ----------------------- drop" << std::endl
              << "∙ {uo} ---------------------- rotate" << std::endl;

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
        // short cuts for p1
        else if (cmd == "a")
        { // move left
            playerManagers[0]->moveBlock('L');
        }
        else if (cmd == "s")
        { // move down
            playerManagers[0]->moveBlock('D');
        }
        else if (cmd == "d")
        { // move right
            playerManagers[0]->moveBlock('R');
        }
        else if (cmd == "w")
        { // drop
            playerManagers[0]->dropBlock();
        }
        else if (cmd == "e")
        { // rotate clockwise
            playerManagers[0]->rotateBlock("CC");
        }
        else if (cmd == "q")
        { // rotate counterclockwise
            playerManagers[0]->rotateBlock("CW");
        }
        // short cuts for p2
        else if (cmd == "j")
        { // move left
            playerManagers[1]->moveBlock('L');
        }
        else if (cmd == "k")
        { // move down
            playerManagers[1]->moveBlock('D');
        }
        else if (cmd == "l")
        { // move right
            playerManagers[1]->moveBlock('R');
        }
        else if (cmd == "i")
        { // drop
            playerManagers[1]->dropBlock();
        }
        else if (cmd == "o")
        { // rotate clockwise
            playerManagers[1]->rotateBlock("CC");
        }
        else if (cmd == "u")
        { // rotate counterclockwise
            playerManagers[1]->rotateBlock("CW");
        }

        else if (cmd == "quit")
        {
            break;
        }
    }
    return 0;
}