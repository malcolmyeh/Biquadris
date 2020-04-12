#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>
#include <fstream>
#include <memory>

class Level
{
protected:
    int levelNumber;
    std::string file;

    std::vector<char> sequence;
    int sequencePosition = 0; // should this be modifiable through ctor?
    void getBlocksFromFile();

public:
    Level(int levelNumber, std::string file);
    ~Level();
    static std::shared_ptr<Level> makeLevel(int level, std::string file);
    virtual char getBlockType();
    int getLevelNumber();
    std::string getFile();
};

#endif