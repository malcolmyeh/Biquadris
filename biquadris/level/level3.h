#ifndef LEVEL3_H
#define LEVEL3_H
#include "level.h"

class Level3 : public Level
{

public:
    Level3(std::string file);
    Level3(std::vector<char> sequence);
    ~Level3();
    std::shared_ptr<Block> createBlock() override;
};

#endif