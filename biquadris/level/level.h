#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>
#include <fstream>

class Level
{
protected:
    std::string file;
    int levelNumber;
    std::vector<char> sequence;
    int sequencePosition = 0; // should this be modifiable throuhg ctor?
    void getBlocksFromFile();

public:
    Level(int levelNumber);
    Level(int levelNumber, std::string file);
    virtual char getBlockType() = 0;
};

#endif