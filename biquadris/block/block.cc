#include "block.h"
#include "dblock.h"
#include "iblock.h"
#include "jblock.h"
#include "lblock.h"
#include "oblock.h"
#include "sblock.h"
#include "tblock.h"
#include "zblock.h"

// ctor 
Block::Block(int colour, Board *board, int level) {
    this->colour = colour;
    this->board = board;
    this->level = level;
}

// this function returns true if it is possible to move in direction (x, y) and false otherwise
//   if move is valid, unfill cells, then refill them after the points have shifted internally
bool Block::move(char direction) {
    // basic board boundary check (R, L, D)
    if (a.getX() + 1 > 10 || a.getX() - 1 < 0 || a.getY() + 1 > 17) 
        return false;

    // translation vector
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
    // convert the block's coordinates into a matrix of 1s and 0s
    std::vector<std::vector<int>> temp(this->recWidth, std::vector<int> (this->recHeight, 0));
    for (int i = 0; i < this->minRec.size(); ++i) {
        Point p{this->minRec[i]};
        if (std::find(std::begin(this->points), std::end(this->points), p) != std::end(this->points)) { // a is in points
            // set it as 1 in the matrix
            temp[this->minRec[i].getX() - this->topLeft.getX()][this->minRec[i].getY() - this->topLeft.getY()] = 1;
        } else {
            // set it as 0 in the matirx
            temp[this->minRec[i].getX() - this->topLeft.getX()][this->minRec[i].getY() - this->topLeft.getY()] = 0;
        }
    }

    // new vars
    std::vector<std::vector<int>> tempCW(this->recHeight, std::vector<int> (this->recWidth, 0));
    std::vector<Point> newPoints;
    std::vector<Point> newMinRec;

    // rotate 1 and 0 matrix
    for (int i = 0; i < recWidth; ++i) {
        for (int j = 0; j < recHeight; ++j) {
            tempCW[j][i] = v[i][recHeight - 1 - j];
        }
    }

    Point newTopLeft{this->topLeft.getX(), this->topLeft.getY() + this->recHeight - this->recWidth};
    for (int i = 0; i < recWidth; ++i) {
        for (int j = 0; j < recHeight; ++j) {
            Point p{newTopLeft.getX() + j, newTopLeft.getY() + i};
            newMinRec.emplace_back(p);
            if (tempCW[j][i] == 1) {
                newPoints.emplace_back(p);
            }
        }
    }

    for (auto a : newPoints) {
        if (this->board.isFilled(a.getX(), a.getY()))
            return false;
    }

    this->points = newPoints;
    this->minRec = newMinRec;
    this->topLeft = newTopLeft;
    std::swap(this->recWidth, this->recHeight);
    return true;
     
}

// it should be possible to drop at anytime..?? so change to void
void Block::drop() {
    while (true) {
        if (!this->move('D'))
            break;
    }
}

// returns true if a block cannot go down further
bool Block::isPlaced() {
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
    return true;
}

bool Block::clearPoint(int row) {
    for (int i = 0; i < this->points.size(); ++i){
        if (this->points[i].getY() == row) {
            this->points.erase(this->points.begin()+i);
            --i;
        }
    }

    return this->points.empty();
}

std::shared_ptr<Block> Block::makeBlock(int colour, Board *board, int level) {
    switch (colour) {
        case Xwindow::Brown:
            return std::make_shared<DBlock>(colour, board, level);
        case Xwindow::Cyan:
            return std::make_shared<IBlock>(colour, board, level);
        case Xwindow::Blue:
            return std::make_shared<JBlock>(colour, board, level);
        case Xwindow::Orange:
            return std::make_shared<LBlock>(colour, board, level);
        case Xwindow::Yellow:
            return std::make_shared<OBlock>(colour, board, level);
        case Xwindow::Green:
            return std::make_shared<SBlock>(colour, board, level);
        case Xwindow::Magenta:
            return std::make_shared<TBlock>(colour, board, level);
        case Xwindow::Red:
            return std::make_shared<ZBlock>(colour, board, level);
    }
}