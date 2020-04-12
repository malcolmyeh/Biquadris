#ifndef LEVEL1_H
#define LEVEL1_H
#include "level.h"

class Level1 : public Level
{
public:
    Level1(std::string file);
    char getBlockType() override;
};

#endif