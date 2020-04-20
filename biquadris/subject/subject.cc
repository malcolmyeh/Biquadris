#include "subject.h"
#include <iostream>

// Subject::Subject(int boadNumber) : boardNumber{boardNumber} {
//   std::cout << "subject created board: " << this->boardNumber << std::endl;
// }

// int Subject::getBoardNumber()
// {
//   return boardNumber;
// }

Subject::Subject(){}

void Subject::attach(std::shared_ptr<View> display)
{
  displays.emplace_back(display);
}