////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-03-16 21:05:07
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 3264
////Problem Title: 
////Run result: Accept
////Run time:0MS
////Run memory:332KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

const int MAXN = 25;
const double PI = 2 * acos(0.0);
const double EPF = 1e-8;

double x[MAXN], y[MAXN], r[MAXN];
int n, T;

double dist(double x1, double y1, double x2, double y2) {
    int xx = x1 - x2, yy = y1 - y2;
    return sqrt(xx * xx + yy * yy);
}

double fusiform(double a, double c, double b) {
    double angle = 2 * acos((a * a + b * b - c * c) / (2 * a * b));
    double s1 = a * a * PI * (angle / (2 * PI));
    double s2 = a * a * sin(angle) / 2;
    return s1 - s2;
}

bool common(double x1, double y1, double r1, double x2, double y2, double r2) {
    double d = dist(x1, y1, x2, y2);
    if(d >= r1 + r2) return false;
    if(d <= fabs(r1 - r2)) {
        if(r1 > r2) return true;
        else return (r1 * r1 * 2 >= r2 * r2);
    }
    double value = fusiform(r1, r2, d) + fusiform(r2, r1, d);
    return value * 2 >= r2 * r2 * PI;
}

bool check(double ox, double oy, double rr) {
    for(int i = 1; i <= n; ++i)
        if(!common(ox, oy, rr, x[i], y[i], r[i])) return false;
    return true;
}

double calc(double ox, double oy) {
    double l = 0, r = 50000;
    while(r - l > 1e-6) {
        double mid = (l + r) / 2;
        if(check(ox, oy, mid)) r = mid;
        else l = mid;
    }
    return l;
}

void solve() {
    double ans = 1e100, value;
    for(int i = 1; i <= n; ++i) {
        value = calc(x[i], y[i]);
        ans = min(ans, value);
    }
    printf("%.4f\n", ans);
}

int main() {
    //cout<<PI<<endl;
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        for(int i = 1; i <= n; ++i) scanf("%lf%lf%lf", &x[i], &y[i], &r[i]);
        solve();
    }
}