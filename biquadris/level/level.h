#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>
#include <fstream>
#include <memory>

#include "../block/dblock.h"
#include "../block/iblock.h"
#include "../block/jblock.h"
#include "../block/lblock.h"
#include "../block/oblock.h"
#include "../block/sblock.h"
#include "../block/tblock.h"
#include "../block/zblock.h"
class Block;

class Level
{
protected:
    int levelNumber;
    std::string file;
    std::vector<char> sequence;
    unsigned int sequencePosition = 0;
    void getBlocksFromFile();
    bool random;

public:
    Level(int levelNumber, std::string file);
    Level(int levelNumber, std::vector<char> sequence);
    virtual ~Level();
    virtual std::shared_ptr<Block> createBlock() = 0;
    int getLevelNumber();
    std::vector<char> getSequence();
    void setRandom(bool random);

};

#endif