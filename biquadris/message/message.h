#ifndef MESSAGE_H
#define MESSAGE_H


#include "../subject/subject.h"

class Player;

class Message : public Subject
{
    std::vector<std::string> text;
    int boardNumber;

public:
    Message(int boardNumber);
    int getBoardNumber();
    void playerWon();
    void specialReady();
    void playing();
    void drawDisplays() override;
    std::vector<std::string> getText();
    void clearMessage();
};

#endif