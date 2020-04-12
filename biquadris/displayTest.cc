#include "display/graphicsdisplay.h"
#include "display/textdisplay.h"
#include "board/board.h"
#include "playermanager.h"
#include "score.h"
#include "block.h"

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
        std::make_shared<PlayerManager>(s1, b1, std::make_shared<Level>(level, levelFile));
    std::shared_ptr<PlayerManager> pm2 =
        std::make_shared<PlayerManager>(s2, b2, std::make_shared<Level>(level, levelFile));

    // link players to each other
    pm1->setOpponent(pm2->getPlayer());
    pm2->setOpponent(pm1->getPlayer());

    // create initial blocks
    pm1->initBlocks();
    pm2->initBlocks();

    std::string cmd;
    while (true)
    {
        std::cin >> cmd;
        if (cmd == "init")
        {
            // link board (+cells), score, display
            std::shared_ptr<TextDisplay> td = std::make_shared<TextDisplay>();
            std::shared_ptr<GraphicsDisplay> gd = std::make_shared<GraphicsDisplay>();
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

            //refresh
            b1->refresh();
            b2->refresh();
            s1->drawDisplays();
            s2->drawDisplays();
        }
        else if (cmd == "1")
        {
            std::cin >> cmd;
            char direction;
            if (cmd == "rotate")
            {
                std::cin >> direction;
                pm1->rotateBlock(direction);
            }
            else if (cmd == "move")
            {
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
            char direction;
            if (cmd == "rotate")
            {
                std::cin >> direction;
                pm2->rotateBlock(direction);
            }
            else if (cmd == "move")
            {
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