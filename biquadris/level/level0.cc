#include "level0.h"

Level0::Level0(std::string filename) : Level{0, filename} {}

char Level0::getBlockType(){
    if (sequencePosition >= sequence.size){
        sequencePosition = 0;
    }
    char blockType = sequence.at(sequencePosition);
    ++sequencePosition;
    return blockType;
}   