#include "block.h"

// ctor 
Block::Block(char type, Board *board) {
    this->type = type;
    this->board = board;
}

// this function returns true if it is possible to move in direction (x, y) and false otherwise
bool Block::move(char direction) {
    for (auto &a : points) {
        // basic board boundary check
        if (a.x + 1 > 10 || a.x - 1 < 0 || a.y + 1 > 17) 
            return false;

        // check for collision with an intermediate block
        if (direction == 'D') {
            for (auto a : this->points) {

            }
        } else if (direction == 'L') {

        } else if (direction == 'R') {
            // create a set of unique Y values that the piece occupies
            std::unordered_set<int> uniqueYValues;
            for (auto a : this->points) {
                if (uniqueYValues.find(a.y) == uniqueYValues.end())
                    uniqueYValues.insert(a.y);
            }

            // set is created. now we find the rightmost point for each Y
            std::vector<Point> checkRight;
            for (auto a : uniqueYValues) {
                int largestX = 0;
                for (auto b : this->points) {
                    if (b.y == a) {
                        if (b.x > largestX) {
                            largestX = b.x;
                        }
                    }
                }
                Point p{largestX, a};
                checkRight.emplace_back(p);
            }

            // check one cell to the right if they are occupied or nah
            for (auto a : checkRight) {
                Point p{a.x + 1, a.y};
                if (isOccupied(p)) { // board.cellGrid[x][y].isFilled
                    return false;
                }
            }

            // finally move points and return true
            for (auto a : this->points) {
                a.x += 1;
            }
            return true;
        }
    }
}

// this function returns true if it is possible to rotate and false if it is not
//   receiving 1 as paramater = CW, 0 = CCW - subject to change
bool Block::rotate(char direction) {
    // this code will (SO FAR) only consider the case where there is nothing inside the "minimum rectangle"
    if (num) { // 1 - CW
        for (auto i : this->points)
    } else { // 0 - CCW

    }
}

// it should be possible to drop at anytime..??
bool Block::drop() {

}
