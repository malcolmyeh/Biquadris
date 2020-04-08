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
        }
        else if (cmd == "r")
        {
            b1.refresh();
            b2.refresh();
        }
        else if (cmd == "b" || cmd == "/")
        {
            b1.toggleBlind();
            b2.toggleBlind();
        }
        else if (cmd == "d" || cmd == ".")
        {
            int x1 = rand() % 11;
            int y1 = rand() % 18;
            int x2 = rand() % 11;
            int y2 = rand() % 18;
            int colour1 = rand() % 7 + 2;
            int colour2 = rand() % 7 + 2;
            b1.draw(x1, y1, colour1);
            b2.draw(x2, y2, colour2);
        }
        else if (cmd == "quit")
        {
            break;
        }
    }

    return 0;
}