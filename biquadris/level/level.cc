#include "level.h"
#include "level0.h"
#include "level1.h"
#include "level2.h"
#include "level3.h"
#include "level4.h"



std::shared_ptr<Level> Level::makeLevel(int level){
    switch (level){
        case 0:
            return std::make_shared<Level0>();
        case 1:
            return std::make_shared<Level1>();
        case 2:
            return std::make_shared<Level2>();
        case 3:
            return std::make_shared<Level3>();
        case 4:
            return std::make_shared<Level4>();
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