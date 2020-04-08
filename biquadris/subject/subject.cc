#include "subject.h"

void Subject::attach(std::shared_ptr<View> display)
{
  displays.emplace_back(display);
}