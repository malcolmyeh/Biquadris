#ifndef MESSAGE_H
#define MESSAGE_H

#include "../subject/subject.h"

class Player;

class Message : public Subject
{
    std::vector<std::string> text;
    int boardNumber;

public:
    // Constructor
    Message(int boardNumber);
    // Getters
    int getBoardNumber();
    std::vector<std::string> getText();
    // Notify Observers
    void drawDisplays() override;
    void playerWon();
    void specialReady();
    void playing();
    void clearMessage();
};

#endif