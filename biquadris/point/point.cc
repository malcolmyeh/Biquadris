#include "point.h"


Point::Point(int x, int y) : x{x}, y{y} {}

int Point::getX() const
{
    return this->x;
}

int Point::getY() const
{
    return this->y;
}

void Point::setX(int x)
{
    this->x = x;
}

void Point::setY(int y)
{
    this->y = y;
}

Point Point::operator+(const Point &other) const
{
    Point sum{this->getX() + other.getX(), this->getY() + other.getY()};
    return sum;
}

Point Point::operator-(const Point &other) const
{
    Point difference{this->getX() - other.getX(), this->getY() - other.getY()};
    return difference;
}

Point &Point::operator+=(const Point &other)
{
    Point sum = this->operator+(other);
    this->x = sum.x;
    this->y = sum.y;
}

Point &Point::operator-=(const Point &other)
{
    Point difference = this->operator-(other);
    this->x = difference.x;
    this->y = difference.y;
}

bool Point::operator==(const Point &other) const {
    return this->x == other.getX() && this->y == other.getY();
}