#ifndef LEVEL4_H
#define LEVEL4_H
#include "level.h"

class Level4 : public Level
{

public:
    Level4(std::string file);
    Level4(std::vector<char> sequence);

    ~Level4();
    std::unique_ptr<Block> createBlock() override;
};

#endif