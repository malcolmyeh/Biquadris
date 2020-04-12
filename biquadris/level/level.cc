#include "level.h"
#include "level0.h"
#include "level1.h"
#include "level2.h"
#include "level3.h"
#include "level4.h"

Level::Level(int levelNumber, std::string file) : levelNumber{levelNumber}, file{file} {}

Level::~Level(){}

std::shared_ptr<Level> Level::makeLevel(int level, std::string file)
{
    switch (level)
    {
    case 0:
        return std::make_shared<Level0>(file);
    case 1:
        return std::make_shared<Level1>(file);
    case 2:
        return std::make_shared<Level2>(file);
    case 3:
        return std::make_shared<Level3>(file);
    case 4:
        return std::make_shared<Level4>(file);
    }
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

int Level::getLevelNumber()
{
    return levelNumber;
}

std::string Level::getFile()
{
    return file;
}