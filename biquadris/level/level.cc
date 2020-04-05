#include "level.h"

Level::Level(int levelNumber) : levelNumber{levelNumber} {}

Level::Level(int levelNumber, std::string file) : levelNumber{levelNumber},
                                                  file{file}
{
    // should we check if file is valid here or in getBlocksFromFile()
    getBlocksFromFile();
}

void Level::getBlocksFromFile()
{
    std::ifstream ifs{file};
    char blockType;
    while (ifs >> blockType)
    {
        sequence.emplace_back(blockType);
    }
}