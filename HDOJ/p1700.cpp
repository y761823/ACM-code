////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-03-16 20:22:52
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 1700
////Problem Title: 
////Run result: Accept
////Run time:0MS
////Run memory:252KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

const double PI = acos(-1.0);
const double EPS = 1e-6;

struct Point {
    double x, y;
};

inline bool operator < (const Point &a, const Point &b) {
    if(fabs(a.y - b.y) < EPS) return a.x < b.x;
    else return a.y < b.y;
}

double xita = PI * 2 / 3;

int main() {
    Point a, b, c;
    int T;
    scanf("%d", &T);
    while(T--) {
        scanf("%lf%lf", &a.x, &a.y);
        b.x = a.x * cos(xita) - a.y * sin(xita);
        b.y = a.y * cos(xita) + a.x * sin(xita);
        c.x = b.x * cos(xita) - b.y * sin(xita);
        c.y = b.y * cos(xita) + b.x * sin(xita);
        if(c < b) swap(b, c);
        printf("%.3f %.3f %.3f %.3f\n", b.x, b.y, c.x, c.y);
    }
}