#include "level.h"

Level::Level(int levelNumber, std::string file) : levelNumber{levelNumber}, file{file} {
    std::cout << file << std::endl;
    this->getBlocksFromFile();
    std::cout << file << std::endl;
}
Level::Level(int levelNumber, std::vector<char> sequence)
    : levelNumber{levelNumber}, sequence{sequence}, sequencePosition{0} {}
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

std::vector<char> Level::getSequence()
{
    return sequence;
}

void Level::setRandom(bool random){
    this->random = random;
}