////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-10-12 15:34:21
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 5017
////Problem Title: 
////Run result: Accept
////Run time:31MS
////Run memory:300KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <ctime>
using namespace std;
typedef long long LL;
#define FOR(i, n) for(int i = 0; i < n; ++i)

double fx[] = {1, -1, 0, 0, 0, 0};
double fy[] = {0, 0, 1, -1, 0, 0};
double fz[] = {0, 0, 0, 0, 1, -1};

double a, b, c, d, e, f;
double x, y, z, res;

double dist(double x, double y, double z) {
    return sqrt(x * x + y * y + z * z);
}

void maintain(double &x, double &y, double &z) {
    double r = sqrt(a * x * x + b * y * y + c * z * z + d * y * z + e * x * z + f * x * y);
    x /= r;
    y /= r;
    z /= r;
}

void move(double step) {
    int f = rand() % 6;
    double nx = x + fx[f] * step;
    double ny = y + fy[f] * step;
    double nz = z + fz[f] * step;
    maintain(nx, ny, nz);
    if(dist(nx, ny, nz) < dist(x, y, z))
        x = nx, y = ny, z = nz;
}

double solve() {
    x = 1e100, y = 0, z = 0;
    maintain(x, y, z);
    for(double step = 1; step > 1e-10; step *= 0.99) {
        move(step);
    }
    return dist(x, y, z);
}

int main() {
    srand(clock());
    while(scanf("%lf%lf%lf%lf%lf%lf", &a, &b, &c, &d, &e, &f) != EOF) {
        printf("%.10f\n", solve());
    }
}
