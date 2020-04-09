#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include <memory>

class View;

class Subject
{
  protected:
  std::vector<std::shared_ptr<View>> displays;

public:

  void attach(std::shared_ptr<View> display);
  virtual void drawDisplays() = 0;
};

#endif