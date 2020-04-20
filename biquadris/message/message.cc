#include "message.h"
#include "../board/board.h"
#include "../display/view.h"

Message::Message(int boardNumber) :boardNumber{boardNumber} {}

void Message::playerWon()
{
    text.clear();
    text.emplace_back("P" + std::to_string(boardNumber) + " has won!");
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

void Message::playing()
{
    text.clear();
    text.emplace_back("[PLAYING]");
    drawDisplays();
}

void Message::clearMessage()
{
    for (auto &display : displays)
        display.lock()->clearMessage(*this);
}

void Message::drawDisplays()
{
    for (auto &display : displays)
        display.lock()->drawMessage(*this);
}

std::vector<std::string> Message::getText()
{
    return text;
}

int Message::getBoardNumber(){
    return boardNumber;
}