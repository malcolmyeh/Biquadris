#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include <memory>

class View;

class Subject
{
protected:
  std::vector<std::weak_ptr<View>> displays;

public:
  Subject();
  void attach(std::shared_ptr<View> display);
  // Notify observers
  virtual void drawDisplays() = 0;
};

#endif