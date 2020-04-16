#ifndef MESSAGE_H
#define MESSAGE_H


#include "../subject/subject.h"

class Player;

class Message : public Subject
{
    std::vector<std::string> text;

public:
    Message(std::shared_ptr<Board> board);
    void playerWon();
    void specialReady();
    void drawDisplays() override;
    std::vector<std::string> getText();
    void clearMessage();
};

#endif