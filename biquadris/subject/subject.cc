#include "subject.h"

Subject::Subject(std::shared_ptr<Board> board) : board{board} {}

std::shared_ptr<Board> Subject::getBoard()
{
  return board;
}

void Subject::attach(std::shared_ptr<View> display)
{
  displays.emplace_back(display);
}