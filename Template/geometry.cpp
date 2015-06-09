#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
#include <complex>
using namespace std;
typedef long long LL;

const double EPS = 1e-10;
int sgn(double x) {
    return (x > EPS) - (x < -EPS);
}

typedef complex<double> Point;
#define x real()
#define y imag()

double cross(const Point &a, const Point &b) { // res > 0 means a on right
    return a.x * b.y - a.y * b.x;
}
double cross(const Point &o, const Point &a, const Point &b) { // res < 0 means turn right
    return cross(a - o, b - o);
}
Point intersection(const Point &u1, const Point &u2, const Point &v1, const Point &v2) {
    double t = cross(u1 - v1, v1 - v2) / cross(u1 - u2, v1 - v2);
    return u1 + (u2 - u1) * t;
}
