#ifndef CURSESDISPLAY_H
#define CURSESDISPLAY_H

#include "view.h"

class CursesDisplay : public View {

    std::vector<WINDOW *> scoreWindows;
    std::vector<WINDOW *> nextBlockWindows;
    std::vector<WINDOW *> boardWindows;
    std::vector<WINDOW *> messageWindows;

    WINDOW *scoreWindow2;
    void initColours();
    void initScoreWindows();
    void initNextBlockWindows();
    void initBoardWindows();
    void initMessageWindows();
public:
    CursesDisplay();
    ~CursesDisplay();
    void drawCell(Cell &cell) override;
    void drawScore(Score &score) override;
    void drawMessage(Message &message) override;
    void clearMessage(Message &message) override;
};

#endif