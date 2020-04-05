#ifndef LEVEL4_H
#define LEVEL4_H
#include "level.h"

class Level4 : public Level
{
    bool random = false;

public:
    Level4();
    void setRandom(bool b);
    char getBlockType() override;
};

#endif