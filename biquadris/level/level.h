#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>
#include <fstream>
#include <memory>

class Level
{
protected:
    std::string file;
    int levelNumber;
    std::vector<char> sequence;
    int sequencePosition = 0; // should this be modifiable through ctor?
    void getBlocksFromFile();

public:
    Level(int levelNumber, std::string file);
    static std::shared_ptr<Level> makeLevel(int level);
    virtual char getBlockType() = 0;
    int getLevelNumber();
};

#endif