#include "message.h"
#include "../board/board.h"
#include "../display/view.h"

Message::Message(std::shared_ptr<Board> board) : Subject{board} {}

void Message::playerWon()
{
    text.clear();
    text.emplace_back("P" + std::to_string(board->getBoardNumber()) + " has won!");
    text.emplace_back("");
    text.emplace_back("Restart");
    text.emplace_back("Quit");
    drawDisplays();
}

void Message::specialReady()
{
    text.clear();
    text.emplace_back("SA Ready:");
    text.emplace_back("Blind");
    text.emplace_back("Heavy");
    text.emplace_back("Force [x]");
    drawDisplays();
}

void Message::clearMessage()
{
    for (auto &display : displays)
        display->clearMessage();
}

void Message::drawDisplays()
{
    for (auto &display : displays)
        display->drawMessage(*this);
}

std::vector<std::string> Message::getText()
{
    return text;
}