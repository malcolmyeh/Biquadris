#ifndef POINT_H
#define POINT_H


struct Point {
    int x;
    int y;

    Point(int x = 0, int y = 0);
    int getX() const;
    int getY() const;
    Point operator+(const Point &other) const;
    Point operator-(const Point &other) const;
    Point &operator+=(const Point &other);
    Point &operator-=(const Point &other);
    // negate?
    // helper function for rotate?
};
// equal operator?

#endif