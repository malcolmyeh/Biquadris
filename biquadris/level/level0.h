#ifndef LEVEL0_H
#define LEVEL0_H
#include "level.h"

class Level0 : public Level
{
    public:
        Level0(std::string file);
        char getBlockType() override;
        
};

#endif