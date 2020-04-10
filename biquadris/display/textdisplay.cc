#include "textdisplay.h"
// #include "../board/cell.h"
// #include "../board/board.h"
#include "../board/board.h"

#include <iostream>
TextDisplay::TextDisplay()
{
    // initialize character grid with spaces
    for (int r = 0; r < 25; ++r)
    {
        std::vector<char> row;
        for (int r = 0; r < 28; ++r)
        {
            row.emplace_back(' ');
        }
        this->charGrid.emplace_back(row);
    }

    // setting static elements of the character grid
    drawStatic("Level: ", 0);
    drawStatic("Score: ", 1);
    drawStatic("-----------", 2);
    drawStatic("-----------", 21);
    drawStatic("Next: ", 22);
}

void TextDisplay::drawStatic(std::string str, int r)
{
    for (unsigned int i = 0; i < str.length(); ++i)
        charGrid[r][i] = charGrid[r][16 + i] = str[i];
}

void TextDisplay::drawCell(Cell &cell)
{
    int c = cell.getPoint()->getX();
    int r = cell.getPoint()->getY() + 3;
    if (cell.getBoard()->getBoardNumber() == 2)
    {
        c += 16;
    }
    if (cell.getIsBlind())
    {
        charGrid[r][c] = '?';
    }
    else if (cell.isFilled())
    {
        switch (cell.getColour())
        {
        case Xwindow::Cyan:
            charGrid[r][c] = 'I';
            break;
        case Xwindow::Blue:
            charGrid[r][c] = 'J';
            break;
        case Xwindow::Orange:
            charGrid[r][c] = 'L';
            break;
        case Xwindow::Yellow:
            charGrid[r][c] = 'O';
            break;
        case Xwindow::Green:
            charGrid[r][c] = 'S';
            break;
        case Xwindow::Red:
            charGrid[r][c] = 'Z';
            break;
        case Xwindow::Magenta:
            charGrid[r][c] = 'T';
            break;
        }
    }
    else
    {
        charGrid[r][c] = ' ';
    }

    std::cout << "\033[2J\033[1;1H";
    for (auto r : this->charGrid)
    {
        for (auto c : r)
            std::cout << c;
        std::cout << std::endl;
    }
}

void TextDisplay::drawScore(Score &score)
{
    // score cna't be more than 4 digits or will be out of index (seg fault)
    int c = 7;
    if (score.getBoard()->getBoardNumber() == 2)
    {
        c += 16;
    }
    for (unsigned int i = 0; i < score.getLevel().length(); ++i)
        charGrid[0][c + i] = score.getLevel()[i];
    for (unsigned int i = 0; i < score.getScore().length(); ++i)
        charGrid[1][c + i] = score.getScore()[i];
    std::cout << "\033[2J\033[1;1H";
    for (auto r : this->charGrid)
    {
        for (auto c : r)
            std::cout << c;
        std::cout << std::endl;
    }
}

std::ostream &operator<<(std::ostream &out, const TextDisplay &td)
{
    for (auto r : td.charGrid)
    {
        for (auto c : r)
            out << c;
        out << std::endl;
    }
    return out;
}