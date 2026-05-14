#include "triangle.h"
#include <cmath>
#include <iostream>

using namespace std;

void distance(Point &P1, Point &P2, double &d) {
    d = std::sqrt(std::pow(P2.x - P1.x, 2) + std::pow(P2.y - P1.y, 2));
}

void isNearlyEqual(double val1, double val2, bool &isEq) {
    double difference = std::fabs(val1 - val2);
    
    if (difference <= std::numeric_limits<double>::min()) {
        isEq = true;
        return;
    }
    
    isEq = difference <= (std::numeric_limits<double>::epsilon() * std::max(std::fabs(val1), std::fabs(val2)) * 32.0);
}

void heronArea(Triangle &t, double &area) {
    double side1 = 0.0, side2 = 0.0, side3 = 0.0;
    
    distance(t.A, t.B, side1);
    distance(t.B, t.C, side2);
    distance(t.C, t.A, side3);
    
    double s = (side1 + side2 + side3) / 2.0;
    area = std::sqrt(s * (s - side1) * (s - side2) * (s - side3));
}

void isTriangleReal(Triangle &t, bool &result) {
    double currentArea;
    t.area(currentArea);
    
    bool isZeroArea;
    isNearlyEqual(currentArea, 0.0, isZeroArea);
    
    result = !isZeroArea;
}

void crossProduct(Point &p1, Point &p2, Point &p3, double &res) {
    res = (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
}

void Triangle::area(double &res) {
    double crossVal;
    crossProduct(A, B, C, crossVal);
    res = std::fabs(crossVal) / 2.0;
}

void Triangle::checkPointPositionVector(Point &target) {
    double v1, v2, v3;
    crossProduct(A, B, target, v1);
    crossProduct(B, C, target, v2);
    crossProduct(C, A, target, v3);

    bool zero1, zero2, zero3;
    isNearlyEqual(v1, 0.0, zero1); if (zero1) v1 = 0.0;
    isNearlyEqual(v2, 0.0, zero2); if (zero2) v2 = 0.0;
    isNearlyEqual(v3, 0.0, zero3); if (zero3) v3 = 0.0;

    bool hasPositive = (v1 > 0.0) || (v2 > 0.0) || (v3 > 0.0);
    bool hasNegative = (v1 < 0.0) || (v2 < 0.0) || (v3 < 0.0);

    cout << "[Векторний метод] ";
    
    if (hasPositive && hasNegative) {
        cout << "Точка лежить поза межами трикутника." << endl;
    } 
    else if (v1 == 0.0 || v2 == 0.0 || v3 == 0.0) {
        double lenAB, lenBC, lenCA, lenAT, lenBT, lenCT;

        distance(A, B, lenAB); distance(B, C, lenBC); distance(C, A, lenCA);
        distance(A, target, lenAT); distance(B, target, lenBT); distance(C, target, lenCT);

        bool edge1, edge2, edge3;
        isNearlyEqual(lenAT + lenBT, lenAB, edge1);
        isNearlyEqual(lenBT + lenCT, lenBC, edge2);
        isNearlyEqual(lenCT + lenAT, lenCA, edge3);

        if (edge1 || edge2 || edge3) {
            cout << "Точка лежить на грані (стороні) трикутника." << endl;
        } else {
            cout << "Точка лежить поза межами трикутника." << endl;
        }
    } 
    else {
        cout << "Точка розташована всередині фігури." << endl;
    }
}

void Triangle::checkPointPositionByArea(Point &target) {
    Triangle tr1 = {A, B, target};
    Triangle tr2 = {B, C, target};
    Triangle tr3 = {C, A, target};

    double mainArea, s1, s2, s3;
    this->area(mainArea);
    tr1.area(s1);
    tr2.area(s2);
    tr3.area(s3);

    double sumOfAreas = s1 + s2 + s3;
    bool areasMatch;
    
    isNearlyEqual(sumOfAreas, mainArea, areasMatch);

    cout << "[Метод площ] ";

    if (!areasMatch) {
        cout << "Точка лежить поза межами трикутника." << endl;
        return;
    }

    bool isDegenerate;
    isNearlyEqual(mainArea, 0.0, isDegenerate);
    
    if (isDegenerate) {
        double l1, l2, l3, d1, d2, d3;
        distance(A, B, l1); distance(B, C, l2); distance(C, A, l3);
        distance(A, target, d1); distance(B, target, d2); distance(C, target, d3);

        bool match1, match2, match3;
        isNearlyEqual(d1 + d2, l1, match1);
        isNearlyEqual(d2 + d3, l2, match2);
        isNearlyEqual(d3 + d1, l3, match3);

        if (match1 || match2 || match3) {
            cout << "Точка лежить на грані (стороні) трикутника." << endl;
        } else {
            cout << "Точка лежить поза межами трикутника." << endl;
        }
        return;
    }

    bool bound1, bound2, bound3;
    isNearlyEqual(s1, 0.0, bound1);
    isNearlyEqual(s2, 0.0, bound2);
    isNearlyEqual(s3, 0.0, bound3);

    if (bound1 || bound2 || bound3) {
        cout << "Точка лежить на грані (стороні) трикутника." << endl;
    } else {
        cout << "Точка розташована всередині фігури." << endl;
    }
}

void startingPoint() {
    Triangle myTri{};

    cout << "--- Введення координат трикутника ---" << endl;
    cout << "Введіть координати точки A (x y): ";
    cin >> myTri.A.x >> myTri.A.y;
    cout << "Введіть координати точки B (x y): ";
    cin >> myTri.B.x >> myTri.B.y;
    cout << "Введіть координати точки C (x y): ";
    cin >> myTri.C.x >> myTri.C.y;

    bool isValid;
    isTriangleReal(myTri, isValid);
    if (!isValid) {
        cout << "Увага: Введений трикутник є виродженим (точки на одній прямій)!" << endl;
    }
    
    int ptsCount;
    cout << "\nСкільки точок бажаєте перевірити? ";
    cin >> ptsCount;
    
    if (ptsCount <= 0) {
        cout << "Помилка: Кількість точок має бути більшою за нуль.\n";
        return;
    }
    
    cout << "-------------------------------------" << endl;
    
    for (int k = 0; k < ptsCount; k++) {
        Point pt = {0, 0};
        cout << "-> Координати точки №" << k + 1 << " (x y): ";
        cin >> pt.x >> pt.y;

        myTri.checkPointPositionVector(pt);
        myTri.checkPointPositionByArea(pt);
        cout << endl;
    }
}
