
#include "ViveTracker.h"
#include "Geom.h"

Point Point::operator*(double t) const {
    return {X * t, Y * t, Z * t};
}

Point Point::operator+(const Point &a) const {
    return {X + a.X, Y + a.Y, Z + a.Z};
}

Point Point::Cross(const Point &rhs) const {
    return {
            Y * rhs.Z - rhs.Y * Z,
            rhs.X * Z - X * rhs.Z,
            X * rhs.Y - rhs.X * Y
    };
}

Point Line::at(double t) const {
    return origin + dir * t;
}

Line::Line(const Point &origin, const Vec &dir) : origin(origin), dir(dir) {}

Line::Line() {

}

Line Plane::Intersection(const Plane &p) const {
    Point dir = Point{A, B, C}.Cross({p.A, p.B, p.C});
    // Handle this case later
    assert(dir.Z != 0);
    double A1 = A, B1 = B, C1 = C, D1 = D;
    double A2 = p.A, B2 = p.B, C2 = p.C, D2 = p.D;
    Point start;
    start.Z = 0;
    start.X = -((-B2*D1+B1*D2)/(A2*B1-A1*B2));
    start.Y = -((A2*D1-A1*D2)/(A2*B1-A1*B2));
    return Line(start, dir);
}