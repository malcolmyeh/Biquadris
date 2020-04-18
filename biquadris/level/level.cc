#include "level.h"

Level::Level(int levelNumber, std::string file) : levelNumber{levelNumber}, file{file} {}
Level::Level(int levelNumber, std::vector<char> sequence, unsigned int sequencePosition)
    : levelNumber{levelNumber}, sequence{sequence}, sequencePosition{sequencePosition} {}
Level::~Level() {}

void Level::getBlocksFromFile()
{
    if (!file.empty())
    {
        std::ifstream ifs{file};
        char blockType;
        while (ifs >> blockType)
        {
            sequence.emplace_back(blockType);
        }
    }
}

int Level::getLevelNumber()
{
    return levelNumber;
}

std::string Level::getFile()
{
    return file;
}