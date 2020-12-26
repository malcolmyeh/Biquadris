#include "subject.h"

Subject::Subject(){}

void Subject::attach(std::shared_ptr<View> display)
{
  displays.emplace_back(display);
}