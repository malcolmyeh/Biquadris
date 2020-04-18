#ifndef LEVEL0_H
#define LEVEL0_H
#include "level.h"

class Level0 : public Level
{
public:
    Level0(std::string file);
    Level0(std::vector<char> sequence, unsigned int sequencePosition);
    ~Level0();
    std::shared_ptr<Block> createBlock() override;
};

#endif