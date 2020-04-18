#ifndef LEVEL4_H
#define LEVEL4_H
#include "level.h"

class Level4 : public Level
{
    bool random = false;

public:
    Level4(std::string file);
    Level4(std::vector<char> sequence, unsigned int sequencePosition);

    ~Level4();
    void setRandom(bool random);
    std::shared_ptr<Block> createBlock() override;
};

#endif