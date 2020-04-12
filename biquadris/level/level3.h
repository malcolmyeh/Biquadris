#ifndef LEVEL3_H
#define LEVEL3_H
#include "level.h"

class Level3 : public Level
{
    bool random = true;

public:
    Level3(std::string file);
    ~Level3();
    void setRandom(bool random);
    std::shared_ptr<Block> createBlock() override;
};

#endif