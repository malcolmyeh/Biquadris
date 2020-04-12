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

    std::cout << "#####################################################################" << std::endl;
    std::cout << "############################ CHECKPOINT #############################" << std::endl;
    std::cout << "#####################################################################" << std::endl;

    std::string cmd;
    while (true)
    {
        std::cin >> cmd;
        if (cmd == "init")
        {
            // link board (+cells), score, display
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
        }
        else if (cmd == "refresh")
        {

            //refresh
            b1->refresh();
            b2->refresh();
            s1->drawDisplays();
            s2->drawDisplays();
        }
        else if (cmd == "initblocks")
        {
            // create initial blocks
            pm1->initBlocks();
            pm2->initBlocks(); // create initial blocks
            std::cout << "#####################################################################" << std::endl;
            std::cout << "############################ INIT BLOCK #############################" << std::endl;
            std::cout << "#####################################################################" << std::endl;
        }
        else if (cmd == "d")
        {
            int x1 = rand() % 11;
            int y1 = rand() % 18;
            int x2 = rand() % 11;
            int y2 = rand() % 18;
            int colour1 = rand() % 7 + 2;
            int colour2 = rand() % 7 + 2;
            b1->fillCell(Point{x1, y1}, colour1);
            b2->fillCell(Point{x2, y2}, colour2);
        }
        else if (cmd == "02")
        {
            int x1 = 0;
            int y1 = 2;
            int x2 = 2;
            int y2 = 2;
            int colour1 = rand() % 7 + 2;
            int colour2 = rand() % 7 + 2;
            b1->fillCell(Point{x1, y1}, colour1);
            b2->fillCell(Point{x2, y2}, colour2);
        }
        else if (cmd == "1")
        {
            std::cin >> cmd;

            if (cmd == "rotate")
            {
                std::string direction;
                std::cin >> direction;
                pm1->rotateBlock(direction);
            }
            else if (cmd == "move")
            {
                char direction;
                std::cin >> direction;

                pm1->moveBlock(direction);
            }
            else if (cmd == "drop")
            {
                pm1->dropBlock();
            }
        }
        else if (cmd == "2")
        {
            std::cin >> cmd;
            if (cmd == "rotate")
            {
                std::string direction;
                std::cin >> direction;
                pm2->rotateBlock(direction);
            }
            else if (cmd == "move")
            {
                char direction;
                std::cin >> direction;

                pm2->moveBlock(direction);
            }
            else if (cmd == "drop")
            {
                pm2->dropBlock();
            }
        }
        else if (cmd == "quit")
        {
            break;
        }
    }
    return 0;
}