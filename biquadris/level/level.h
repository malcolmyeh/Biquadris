#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>

class Level
{
    std::string file;
    int levelNumber;
    bool random = false;
    std::vector<char> sequence;

public:
    virtual char getBlockType() = 0;
    virtual void generateSequence() = 0;
    void setRandom(bool b);
};

#endif