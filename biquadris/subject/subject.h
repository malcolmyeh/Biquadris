#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include <memory>

class View;
class Board;

class Subject
{
  protected:
  std::vector<std::shared_ptr<View>> displays;
  // std::shared_ptr<Board> board;
  // int boardNumber;

public:
  Subject();
  // int getBoardNumber();
  void attach(std::shared_ptr<View> display);
  virtual void drawDisplays() = 0;
};

#endif