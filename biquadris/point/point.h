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

    Point operator+(const Point &other) const;
    Point operator-(const Point &other) const;
    Point &operator+=(const Point &other);
    Point &operator-=(const Point &other);
    bool operator==(const Point &other) const;

};

#endif