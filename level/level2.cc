#include "level2.h"

Level2::Level2(std::string file) : Level{2, file} {}
Level2::Level2(std::vector<char> sequence): Level{2, sequence}{}

Level2::~Level2() {}

std::unique_ptr<Block> Level2::createBlock()
{
    std::unique_ptr<Block> block;
    switch (rand() % 7)
    {
    case 0:
        block = std::make_unique<IBlock>(levelNumber);
        break;
    case 1:
        block = std::make_unique<JBlock>(levelNumber);
        break;
    case 2:
        block = std::make_unique<LBlock>(levelNumber);
        break;
    case 3:
        block = std::make_unique<OBlock>(levelNumber);
        break;
    case 4:
        block = std::make_unique<SBlock>(levelNumber);
        break;
    case 5:
        block = std::make_unique<TBlock>(levelNumber);
        break;
    case 6:
        block = std::make_unique<ZBlock>(levelNumber);
        break;
    }
    return block;
}