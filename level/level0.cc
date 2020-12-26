#include "level0.h"

Level0::Level0(std::string file) : Level{0, file} {}
Level0::Level0(std::vector<char> sequence)
: Level{0, sequence}{}
Level0::~Level0() {}

std::unique_ptr<Block> Level0::createBlock()
{
    if (sequencePosition >= sequence.size())
    {
        sequencePosition = 0;
    }
    std::unique_ptr<Block> block;
    switch (sequence.at(sequencePosition))
    {
    case 'I':
        block = std::make_unique<IBlock>(levelNumber);
        break;
    case 'J':
        block = std::make_unique<JBlock>(levelNumber);
        break;
    case 'L':
        block = std::make_unique<LBlock>(levelNumber);
        break;
    case 'O':
        block = std::make_unique<OBlock>(levelNumber);
        break;
    case 'S':
        block = std::make_unique<SBlock>(levelNumber);
        break;
    case 'Z':
        block = std::make_unique<ZBlock>(levelNumber);
        break;
    case 'T':
        block = std::make_unique<TBlock>(levelNumber);
        break;
    }
    ++sequencePosition;
    return block;
}