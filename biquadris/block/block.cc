#include "block.h"

// ctor 
Block::Block(char type, Board *board) {
    this->type = type;
    this->board = board;
}

// this function returns true if it is possible to move in direction (x, y) and false otherwise
bool Block::move(char direction) {
    // basic board boundary check (R, L, D)
    if (a.getX() + 1 > 10 || a.getX() - 1 < 0 || a.getY() + 1 > 17) 
        return false;

    Point p{0, 0};

    // check for collision with an intermediate block
    if (direction == 'D') {
        // create a set of unique X values which the piece occupies
        std::unordered_set<int> uniqueXValues;
        for (auto a : this->points) {
            if (uniqueXValues.find(a.getX()) == uniqueXValues.end())
                uniqueXValues.insert(a.getX());
        }

        // now that the set is created, find the lowermost points for each unique X
        std::vector<Point> checkDown;
        for (auto a : uniqueXValues) {
            int largestY = 0;
            for (auto b : this->points) {
                if (b.getX() == a) {
                    if (b.getY() > largestY) {
                        largestY = b.getY();
                    }
                }
            }
            Point p{a, largestY};
            checkDown.emplace_back(p);
        }

        // vector of lowest bound of piece created. check one below.
        for (auto a : checkDown) {
            if (this->board.isFilled(a.getX(), a.getY() + 1)) // if one of these points are filled->false
                return false;
        }

        p = {0, 1};
    } else if (direction == 'L') {
        std::unordered_set<int> uniqueYValues;
        for (auto a : this->points) {
            if (uniqueYValues.find(a.getY()) == uniqueYValues.end()) // it is not there? insert
                uniqueYValues.insert(a.getY());
        }

        std::vector<Point> checkLeft;
        for (auto a : uniqueYValues) {
            int smallestX = 10;
            for (auto b : this->points) {
                if (b.getY() == a) {
                    if (b.getX() < smallestX) {
                        smallestX = b.getX();
                    }
                }
            }
            Point p{smallestX, a};
            checkLeft.emplace_back(p);
        }

        for (auto a : checkLeft) {
            if (this->board.isFilled(a.getX() - 1, a.getY()))
                return false;
        }

        p = {-1, 0};
    } else if (direction == 'R') {
        // create a set of unique Y values that the piece occupies
        std::unordered_set<int> uniqueYValues;
        for (auto a : this->points) {
            if (uniqueYValues.find(a.getY()) == uniqueYValues.end())
                uniqueYValues.insert(a.getY());
        }

        // set is created. now we find the rightmost point for each Y
        std::vector<Point> checkRight;
        for (auto a : uniqueYValues) {
            int largestX = 0;
            for (auto b : this->points) {
                if (b.getY() == a) {
                    if (b.getX() > largestX) {
                        largestX = b.getX();
                    }
                }
            }
            Point p{largestX, a};
            checkRight.emplace_back(p);
        }

        // check one cell to the right if they are occupied or nah
        for (auto a : checkRight) {
            if (this->board.isFilled(a.getX() + 1, a.getY()))
                return false;
        }

        p = {1, 0};
    }
    for (auto a : this->points) {
        a += p;
    }
    for (auto a : this->minRec) {
        a += p;
        // if (std::find(this->points.begin(), this->points.end(), a) != this->points.end()) { // if a is in points

        // }
    }
    this->topLeft += p;
    return true;
}


// this function returns true if it is possible to rotate and false if it is not
//   if any of the new position cells are filled, then it's not a valid rotation
bool Block::rotate(std::string direction) {
    // convert the block's coordinates into a matrix of ints
    std::vector<std::vector<int>> v;


}

// it should be possible to drop at anytime..?? so change to void
void Block::drop() {
    while (true) {
        if (!this->move('D'))
            break;
    }
}
