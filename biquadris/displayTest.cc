#include "display/graphicsdisplay.h"
#include "display/textdisplay.h"
#include "board/board.h"
#include <memory>
#include <string>
#include <sstream>
#include <iostream>

int main(int argc, char *argv[])
{
    Board b1;
    Board b2;
    Score s1(1, 1);
    Score s2(2, 2);
    std::string cmd;
    while (true)
    {
        std::cin >> cmd;
        if (cmd == "init")
        {
            std::shared_ptr<TextDisplay> td = std::make_shared<TextDisplay>();
            std::shared_ptr<GraphicsDisplay> gd = std::make_shared<GraphicsDisplay>();
            b1.init(1);
            b2.init(2);
            b1.setDisplay(td);
            b1.setDisplay(gd);
            b2.setDisplay(td);
            b2.setDisplay(gd);
            s1.attach(td);
            s1.attach(gd);
            s2.attach(td);
            s2.attach(gd);
        }
        else if (cmd == "r")
        {
            b1.refresh();
            b2.refresh();
            s1.drawDisplays();
            s2.drawDisplays();
        }
        else if (cmd == "b")
        {
            b1.toggleBlind();
            b2.toggleBlind();
        }
        else if (cmd == "d")
        {
            int x1 = rand() % 11;
            int y1 = rand() % 18;
            int x2 = rand() % 11;
            int y2 = rand() % 18;
            int colour1 = rand() % 7 + 2;
            int colour2 = rand() % 7 + 2;
            b1.fillCell(Point{x1, y1}, colour1);
            b2.fillCell(Point{x2, y2}, colour2);
        }
        else if (cmd == "l")
        {
            s1.changeLevel(std::stoi(s1.getLevel()) + 1);
            s2.changeLevel(std::stoi(s2.getLevel()) + 1);
        }
        else if (cmd == "s")
        {
            s1.updateScoreRow(4);
            s2.updateScoreRow(4);
        }
        else if (cmd == "quit")
        {
            break;
        }
    }

    return 0;
}