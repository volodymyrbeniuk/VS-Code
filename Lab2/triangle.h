#ifndef GEOMETRY_LAB_H
#define GEOMETRY_LAB_H

struct Point {
    double x, y;
};

struct Triangle {
    Point A, B, C;

    void area(double &outputArea);
    void checkPointPositionVector(Point &target);
    void checkPointPositionByArea(Point &target);
};

void distance(Point &p1, Point &p2, double &dist);
void isNearlyEqual(double val1, double val2, bool &isEq);
void heronArea(Triangle &tr, double &res);
void isTriangleReal(Triangle &tr, bool &isValid);
void crossProduct(Point &a, Point &b, Point &c, double &val);
void startingPoint();

#endif