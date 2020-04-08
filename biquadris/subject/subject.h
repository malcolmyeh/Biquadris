#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include <memory>

// #include "../point/point.h"

class View;

class Subject
{
  protected:
  // Point point;
  std::vector<std::shared_ptr<View>> displays;
  // int boardNumber;

public:

  void attach(std::shared_ptr<View> display);
  // int getBoardNumber();
  // Point getPoint();
  virtual void drawDisplays() = 0;
};




// int Subject::getBoardNumber(){
//   return boardNumber;
// }

// Point Subject::getPoint(){
//   return point;
// }

#endif