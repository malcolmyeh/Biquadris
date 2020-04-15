#include "block.h"
#include "../board/board.h"

// ctor
Block::Block(int colour, int level)
{
    this->colour = colour;
    this->level = level;
}

// this function returns true if it is possible to move in direction (x, y) and false otherwise
//   if move is valid, unfill cells, then refill them after the points have shifted internally

// MAKE SURE I CHECK FOR BOUNDARIES AND SEG FAULTS ASAP
bool Block::move(char direction)
{
    std::cout << "Block::move" << std::endl;
    // translation vector
    Point p{0, 0};
    // std::cout << "BEFORE MOVE" << std::endl;
    // for (a : this->points) {
    //     std::cout << a.getX() << ", " << a.getY() << std::endl;
    // }
    // check for collision with an intermediate block
    if (direction == 'D')
    {
        // create a set of unique X values which the piece occupies
        std::unordered_set<int> uniqueXValues;
        for (auto a : this->points)
        {
            if (uniqueXValues.find(a.getX()) == uniqueXValues.end())
                uniqueXValues.insert(a.getX());
        }

        // now that the set is created, find the lowermost points for each unique X
        std::vector<Point> checkDown;
        for (auto a : uniqueXValues)
        {
            int largestY = 0;
            for (auto b : this->points)
            {
                if (b.getX() == a)
                {
                    if (b.getY() > largestY)
                    {
                        largestY = b.getY();
                    }
                }
            }
            Point p{a, largestY};
            checkDown.emplace_back(p);
        }

        // vector of lowest bound of piece created. check one below.
        for (auto a : checkDown)
        {
            // check bottom boundary
            if (a.getY() + 1 > 17)
                return false;
            // check if piece is occupying
            Point q{a.getX(), a.getY() + 1};
            if (this->board->isFilled(q)) // if one of these points are filled->false
                return false;
        }

        // empty the current cells
        std::cout << "Can move down. Current coordinates: " << std::endl;
        this->printCellCoordinates();
        std::cout << "Clearing original cells..." << std::endl;
        this->drawBlock(Xwindow::White);

        p = {0, 1};
    }
    else if (direction == 'L')
    {
        std::unordered_set<int> uniqueYValues;
        for (auto a : this->points)
        {
            if (uniqueYValues.find(a.getY()) == uniqueYValues.end()) // it is not there? insert
                uniqueYValues.insert(a.getY());
        }

        std::vector<Point> checkLeft;
        for (auto a : uniqueYValues)
        {
            int smallestX = 10;
            for (auto b : this->points)
            {
                if (b.getY() == a)
                {
                    if (b.getX() < smallestX)
                    {
                        smallestX = b.getX();
                    }
                }
            }
            Point p{smallestX, a};
            checkLeft.emplace_back(p);
        }

        for (auto a : checkLeft)
        {
            if (a.getX() - 1 < 0)
                return false;
            Point q{a.getX() - 1, a.getY()};
            if (this->board->isFilled(q))
                return false;
        }

        std::cout << "Can move left. Current coordinates: " << std::endl;
        this->printCellCoordinates();
        std::cout << "Clearing original cells..." << std::endl;
        this->drawBlock(Xwindow::White);
        p = {-1, 0};
    }
    else if (direction == 'R')
    {
        // create a set of unique Y values that the piece occupies
        std::unordered_set<int> uniqueYValues;
        for (auto a : this->points)
        {
            if (uniqueYValues.find(a.getY()) == uniqueYValues.end())
                uniqueYValues.insert(a.getY());
        }

        // set is created. now we find the rightmost point for each Y
        std::vector<Point> checkRight;
        for (auto a : uniqueYValues)
        {
            int largestX = 0;
            for (auto b : this->points)
            {
                if (b.getY() == a)
                {
                    if (b.getX() > largestX)
                    {
                        largestX = b.getX();
                    }
                }
            }
            Point p{largestX, a};
            checkRight.emplace_back(p);
        }

        // check one cell to the right if they are occupied or nah
        for (auto a : checkRight)
        {
            if (a.getX() + 1 > 10)
                return false;
            Point q{a.getX() + 1, a.getY()};
            // if (this->board->isFilled(a.getX() + 1, a.getY()))
            if (this->board->isFilled(q))
                return false;
        }

        std::cout << "Can move down. Current coordinates: " << std::endl;
        this->printCellCoordinates();
        std::cout << "Clearing original cells..." << std::endl;
        this->drawBlock(Xwindow::White);
        p = {1, 0};
    }
    std::cout << "P: {" << p.getX() << "," << p.getY() << "}" << std::endl;
    std::cout << "moving current cells" << std::endl;
    for (auto &a : this->points)
    {
        std::cout << "a before: {" << a.getX() << "," << a.getY() << "}" << std::endl;
        a += p;
        std::cout << "a after: {" << a.getX() << "," << a.getY() << "}" << std::endl;
    }
    for (auto &a : this->minRec)
    {
        a += p;
        // if (std::find(this->points.begin(), this->points.end(), a) != this->points.end()) { // if a is in points

        // }
    }
    this->topLeft += p;
    std::cout << "Finished moving. Current coordinates: " << std::endl;
    this->printCellCoordinates();
    std::cout << "Filling in new cells..." << std::endl;
    this->drawBlock(this->colour);
    return true;
}

// this function returns true if it is possible to rotate and false if it is not
//   if any of the new position cells are filled, then it's not a valid rotation
bool Block::rotate(std::string direction)
{
    std::cout << "Block::rotate" << std::endl;
    std::cout << "BEFORE ROTATE POINTS" << std::endl;
    this->printCellCoordinates();

    std::vector<std::vector<int>> temp(this->recWidth, std::vector<int>(this->recHeight, 0));
    // convert the block's coordinates into a matrix of 1s and 0s
    for (unsigned int i = 0; i < this->minRec.size(); ++i)
    {
        Point p{this->minRec[i].getX(), this->minRec[i].getY()};
        // if (std::find(std::begin(this->points), std::end(this->points), p) != std::end(this->points)) { // a is in points
        if (std::find(this->points.begin(), this->points.end(), p) != this->points.end())
        { // a is in points
            // set it as 1 in the matrix
            temp[this->minRec[i].getX() - this->topLeft.getX()][this->minRec[i].getY() - this->topLeft.getY()] = 1;
        }
        else
        {
            // set it as 0 in the matirx
            temp[this->minRec[i].getX() - this->topLeft.getX()][this->minRec[i].getY() - this->topLeft.getY()] = 0;
        }
    }

    if (direction == "CW") {
        
        // new vars
        std::vector<std::vector<int>> tempCW(this->recHeight, std::vector<int>(this->recWidth, 0));
        std::vector<Point> newPoints;
        std::vector<Point> newMinRec;

        // rotate 1 and 0 matrix
        for (int i = 0; i < recWidth; ++i)
        {
            for (int j = 0; j < recHeight; ++j)
            {
                tempCW[j][i] = temp[i][recHeight - 1 - j];
            }
        }

        Point newTopLeft{this->topLeft.getX(), this->topLeft.getY() + this->recHeight - this->recWidth};
        for (int i = 0; i < recWidth; ++i)
        {
            for (int j = 0; j < recHeight; ++j)
            {
                Point p{newTopLeft.getX() + j, newTopLeft.getY() + i};
                newMinRec.emplace_back(p);
                if (tempCW[j][i] == 1)
                {
                    newPoints.emplace_back(p);
                }
            }
        }

        std::cout << "AFTER ROTATE POINTS" << std::endl;
        // for (auto a : newPoints)
        //     std::cout << "{" << a.getX() << "," << a.getY() << "} ";
        // std::cout << std::endl;

        for (auto a : newPoints)
        {
            if (a.getX() < 0)
                return false;
            if (a.getX() > 10)
                return false;
            if (a.getY() > 17)
                return false;
        }

        for (auto a : newPoints)
        {   
            if (std::find(this->points.begin(), this->points.end(), a) == this->points.end()) { // a is not in points
                if (this->board->isFilled(a))
                    return false;
            }
            // if (this->board->isFilled(a) && !std::find(this->points.begin(), this->points.end(), a))
            //     return false;
        }
        this->drawBlock(Xwindow::White);
        this->points = newPoints;
        this->printCellCoordinates();
        this->minRec = newMinRec;
        this->topLeft = newTopLeft;
        std::swap(this->recWidth, this->recHeight);
        this->drawBlock(this->colour);
        return true;
    } else if (direction == "CCW") {
        std::vector<std::vector<int>> tempCCW(this->recHeight, std::vector<int>(this->recWidth, 0));
        std::vector<Point> newPoints;
        std::vector<Point> newMinRec;

        for (int i = 0; i < recWidth; ++i) {
            for (int j = 0; j < recHeight; ++j) {
                tempCCW[j][i] = temp[recWidth - 1 - i][j];
            }
        }

        Point newTopLeft{this->topLeft.getX(), this->topLeft.getY() + this->recHeight - this->recWidth};
        for (int i = 0; i < recWidth; ++i) {
            for (int j = 0; j < recHeight; ++j) {
                Point p{newTopLeft.getX() + j, newTopLeft.getY() + i};
                newMinRec.emplace_back(p);
                if (tempCCW[j][i] == 1) {
                    newPoints.emplace_back(p);
                }
            }
        }

        for (auto a : newPoints) {
            if (a.getX() < 0)
                return false;
            if (a.getX() > 10)
                return false;
            if (a.getY() > 17)
                return false;
        }

        for (auto a : newPoints) {
            if (std::find(this->points.begin(), this->points.end(), a) == this->points.end()) {
                if (this->board->isFilled(a))
                    return false;
            }
        }
        this->drawBlock(Xwindow::White);
        this->points = newPoints;
        this->printCellCoordinates();
        this->minRec = newMinRec;
        this->topLeft = newTopLeft;
        std::swap(this->recWidth, this->recHeight);
        this->drawBlock(this->colour);
        return true;
    }
}

// it should be possible to drop at anytime..?? so change to void
void Block::drop()
{
    std::cout << "Block::drop" << std::endl;
    while (true)
    {
        if (!this->move('D'))
            break;
    }
}

// returns true if a block cannot go down further
bool Block::isPlaced()
{
    std::unordered_set<int> uniqueXValues;
    for (auto a : this->points)
    {
        if (uniqueXValues.find(a.getX()) == uniqueXValues.end())
            uniqueXValues.insert(a.getX());
    }

    // now that the set is created, find the lowermost points for each unique X
    std::vector<Point> checkDown;
    for (auto a : uniqueXValues)
    {
        int largestY = 0;
        for (auto b : this->points)
        {
            if (b.getX() == a)
            {
                if (b.getY() > largestY)
                {
                    largestY = b.getY();
                }
            }
        }
        Point p{a, largestY};
        checkDown.emplace_back(p);
    }

    // vector of lowest bound of piece created. check one below.
    for (auto a : checkDown)
    {
        if (a.getY() + 1 > 17)
            return true;
        Point q{a.getX(), a.getY() + 1};
        if (this->board->isFilled(q)) // if one of these points are filled->false
            return true;
    }
    return false;
}

bool Block::clearPoint(int row)
{
    std::cout << "Block::clearPoint" << std::endl;
    for (unsigned int i = 0; i < this->points.size(); ++i)
    {
        if (this->points[i].getY() == row)
        {
            drawBlock(Xwindow::White);
            this->points.erase(this->points.begin() + i);
            drawBlock(this->colour);
            --i;
        }
    }

    return this->points.empty();
}

int Block::getLevel()
{
    return this->level;
}

void Block::setBoard(std::shared_ptr<Board> board)
{
    this->board = board;
    drawBlock(this->colour);
}

void Block::drawBlock(int colour)
{
    for (auto a : this->points)
        this->board->fillCell(a, colour);
}

void Block::printCellCoordinates()
{
    for (auto a : this->points)
        std::cout << "{" << a.getX() << "," << a.getY() << "} ";
    std::cout << std::endl;
}

bool Block::isEmpty() {
    return this->points.empty();
}