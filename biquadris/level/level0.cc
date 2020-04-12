#include "level0.h"

Level0::Level0(std::string file) : Level{0, file} {}

Level0::~Level0(){}

std::shared_ptr<Block> Level0::createBlock()
{
    if (sequencePosition >= sequence.size())
    {
        sequencePosition = 0;
    }
    std::shared_ptr<Block> block;
    switch (sequence.at(sequencePosition))
    {
    case 'I':
        block = std::make_shared<IBlock>(levelNumber);
        break;
    case 'J':
        block = std::make_shared<JBlock>(levelNumber);
        break;
    case 'L':
        block = std::make_shared<LBlock>(levelNumber);
        break;
    case 'O':
        block = std::make_shared<OBlock>(levelNumber);
        break;
    case 'S':
        block = std::make_shared<SBlock>(levelNumber);
        break;
    case 'Z':
        block = std::make_shared<ZBlock>(levelNumber);
        break;
    case 'T':
        block = std::make_shared<TBlock>(levelNumber);
        break;
    }
    ++sequencePosition;
    return block;
}