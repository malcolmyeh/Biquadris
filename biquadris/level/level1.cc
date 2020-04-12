#include "level1.h"

Level1::Level1(std::string file) : Level{1, file} {}

Level1::~Level1(){}

std::shared_ptr<Block> Level1::createBlock()
{
    std::shared_ptr<Block> block;
    switch (rand() % 12)
    {
    case 0:
    case 1:
        block = std::make_shared<IBlock>(levelNumber);
        break;
    case 2:
    case 3:
        block = std::make_shared<JBlock>(levelNumber);
        break;
    case 4:
    case 5:
        block = std::make_shared<LBlock>(levelNumber);
        break;
    case 6:
    case 7:
        block = std::make_shared<OBlock>(levelNumber);
        break;
    case 8:
    case 9:
        block = std::make_shared<TBlock>(levelNumber);
        break;
    case 10:
        block = std::make_shared<SBlock>(levelNumber);
        break;
    case 11:
        block = std::make_shared<ZBlock>(levelNumber);
        break;
    }
    return block;
}