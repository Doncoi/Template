#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define MAXN 100 + 5

const double EPS = 1e-6;
const double Pi = std :: acos(-1.0);

struct Point
{
    Point(){}
    Point(double x, double y) : x(x), y(y) {}
    double x, y;
};

struct Seg
{
    Point p1, p2;
};

double max(double x, double y)
{
    return (x > y ? x : y);
}

double min(double x, double y)
{
    return (x < y ? x : y);
}

int sign(double x)
{
    return (x < -EPS ? -1 : (x > EPS));
}

double cross(const Point &p1,const Point &p2,const Point &p3,const Point &p4)
{
    return (p2.x-p1.x)*(p4.y-p3.y) - (p2.y-p1.y)*(p4.x-p3.x);  
}

double area(const Point &p1, const Point &p2, const Point &p3)  
{  
    return cross(p1, p2, p1, p3);  
}  

double farea(const Point &p1, const Point &p2, const Point &p3)  
{  
    return std :: fabs(area(p1, p2, p3));  
}  

bool meet(const Point &p1,const Point &p2,const Point &p3,const Point &p4)
{
    return 
    max(min(p1.x, p2.x), min(p3.x, p4.x)) <= min(max(p1.x, p2.x), max(p3.x, p4.x))
    &&
    max(min(p1.y, p2.y), min(p3.y, p4.y)) <= min(max(p1.y, p2.y), max(p3.y, p4.y))
    &&
    sign(cross(p3, p2, p3, p4) * cross(p3, p4, p3, p1)) >= 0
    &&
    sign(cross(p1, p4, p1, p2) * cross(p1, p2, p1, p3)) >= 0;
}

Point inter(const Point &p1,const Point &p2,const Point &p3,const Point &p4)
{
    double k = farea(p1, p2, p3) / farea(p1, p2, p4);
    return Point((p3.x + k * p4.x) / (1 + k), (p3.y + k * p4.y) / (1 + k));
}