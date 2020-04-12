#include "level2.h"

Level2::Level2(std::string file) : Level{2, file} {}

Level2::~Level2(){}

std::shared_ptr<Block> Level2::createBlock()
{
    std::shared_ptr<Block> block;
    switch (rand() % 7)
    {
    case 0:
        block = std::make_shared<IBlock>(levelNumber);
        break;
    case 1:
        block = std::make_shared<JBlock>(levelNumber);
        break;
    case 2:
        block = std::make_shared<LBlock>(levelNumber);
        break;
    case 3:
        block = std::make_shared<OBlock>(levelNumber);
        break;
    case 4:
        block = std::make_shared<SBlock>(levelNumber);
        break;
    case 5:
        block = std::make_shared<TBlock>(levelNumber);
        break;
    case 6:
        block = std::make_shared<ZBlock>(levelNumber);
        break;
    }
    return block;
}