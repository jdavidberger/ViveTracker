
#pragma once

#include <map>
#include <vector>

struct Point {
    double X = 0, Y = 0, Z = 0;

    Point operator*(double t) const;
    Point operator+(const Point& a) const;
    Point Cross(const Point& rhs) const;
};

typedef Point Vec;

struct Line {
    Point origin;
    Vec dir = {1, 0, 0};
    Point at(double t) const;

    Line();
    Line(const Point &origin, const Vec &dir);
};

struct Plane {
    double A = 0, B = 0, C = 0, D = 0;
    Line Intersection(const Plane& p) const;
};