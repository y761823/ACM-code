////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-08-15 13:49:20
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 1724
////Problem Title: 
////Run result: Accept
////Run time:93MS
////Run memory:332KB
//////////////////System Comment End//////////////////
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;

double fa, fb, fl, fr;
int n;

double sqr(double x) {
    return x * x;
}

double func(double x) {
    return  2 * sqrt(sqr(fb) * (1 - sqr(x) / sqr(fa)));
}

double simpson(double a, double b) {
    double mid = a + (b - a) / 2;
    return (func(a) + 4 * func(mid) + func(b)) * (b - a) / 6;
}

double asr(double a, double b, double eps, double A) {
    double mid = a + (b - a) / 2;
    double l = simpson(a, mid), r = simpson(mid, b);
    if(fabs(l + r - A) <= 15 * eps) return l + r + (l + r - A) / 15;
    return asr(a, mid, eps / 2, l) + asr(mid, b, eps / 2, r);
}

double asr(double a, double b, double eps) {
    return asr(a, b, eps, simpson(a, b));
}

int main() {
    scanf("%d", &n);
    while(n--) {
        scanf("%lf%lf%lf%lf", &fa, &fb, &fl, &fr);
        printf("%.3f\n", asr(fl, fr, 1e-5));
    }
}
