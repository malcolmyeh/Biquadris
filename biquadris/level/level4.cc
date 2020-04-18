#include "level4.h"

Level4::Level4(std::string file) : Level{4, file} {}
Level4::Level4(std::vector<char> sequence)
    : Level{4, sequence} {}

Level4::~Level4() {}

std::shared_ptr<Block> Level4::createBlock()
{
    std::shared_ptr<Block> block;
    if (random)
    {
        switch (rand() % 9)
        {
        case 0:
        case 1:
            block = std::make_shared<SBlock>(levelNumber);
            break;
        case 2:
        case 3:
            block = std::make_shared<ZBlock>(levelNumber);
            break;
        case 4:
            block = std::make_shared<IBlock>(levelNumber);
            break;
        case 5:
            block = std::make_shared<JBlock>(levelNumber);
            break;
        case 6:
            block = std::make_shared<LBlock>(levelNumber);
            break;
        case 7:
            block = std::make_shared<OBlock>(levelNumber);
            break;
        case 8:
            block = std::make_shared<TBlock>(levelNumber);
            break;
        }
    }
    else
    {
        if (sequencePosition >= sequence.size())
        {
            sequencePosition = 0;
        }
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
    }
    return block;
}