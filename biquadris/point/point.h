#ifndef POINT_H
#define POINT_H

class Point
{
    int x;
    int y;

public:
    Point(int x = 0, int y = 0);
    int getX() const;
    int getY() const;
    void setX(int x);
    void setY(int y);
    Point operator+(const Point &other) const;
    Point operator-(const Point &other) const;
    Point &operator+=(const Point &other);
    Point &operator-=(const Point &other);
};

#endif