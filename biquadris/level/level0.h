#ifndef LEVEL0_H
#define LEVEL0_H
#include "level.h"

class Level0 : public Level
{
public:
    Level0(std::string file);
    Level0(std::vector<char> sequence);
    ~Level0();
    std::unique_ptr<Block> createBlock() override;
};

#endif