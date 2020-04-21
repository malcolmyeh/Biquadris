#include "textdisplay.h"

#include "../board/board.h"

#include <iostream>
TextDisplay::TextDisplay()
{
    // initialize character grid with spaces
    for (int r = 0; r < 30; ++r)
    {
        std::vector<char> row;
        for (int c = 0; c < 28; ++c)
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
    drawStatic("Next: Hold:", 22);
}

void TextDisplay::drawStatic(std::string str, int r)
{
    // draws for both boards
    for (unsigned int i = 0; i < str.length(); ++i)
        charGrid[r][i] = charGrid[r][16 + i] = str[i];
}

void TextDisplay::drawCell(Cell &cell)
{
    Point adjusted = cell.getPoint() + cell.getOrigin();
    int c = adjusted.getX();
    int r = adjusted.getY();
    if (cell.getBoardNumber() == 2)
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
        case Xwindow::Brown:
            charGrid[r][c] = 'D';
            break;
        }
    }
    else
    {
        charGrid[r][c] = ' ';
    }
    draw();
}

void TextDisplay::drawScore(Score &score)
{
    int c = 7;
    if (score.getBoardNumber() == 2)
    {
        c += 16;
    }
    for (unsigned int i = 0; i < score.getLevel().length(); ++i)
        charGrid[0][c + i] = score.getLevel()[i];
    for (unsigned int i = 0; i < score.getScore().length(); ++i)
        charGrid[1][c + i] = score.getScore()[i];
    draw();
}

void TextDisplay::drawMessage(Message &message)
{
    int c = 0;
    int r = 26;
    if (message.getBoardNumber() == 2)
    {
        c += 16;
    }
    for (unsigned int i = 0; i < message.getText().size(); ++i)
    {
        for (unsigned int j = 0; j < message.getText()[i].length(); ++j)
            charGrid[r + i][c + j] = message.getText()[i][j];
    }
    draw();
}

void TextDisplay::clearMessage(Message &message)
{
    for (int r = 26; r < 30; ++r){
        for (int c = 0; c < 28; ++c)
            charGrid[r][c] = ' ';
    }
    draw();
}

// Prints to screen
void TextDisplay::draw()
{
    std::cout << "\033[2J\033[1;1H"; // Clear screen
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