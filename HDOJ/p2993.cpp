////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-08-26 23:53:40
////Compiler: Visual C++
//////////////////////////////////////////////////////
////Problem ID: 2993
////Problem Title: 
////Run result: Accept
////Run time:500MS
////Run memory:652KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <ctime>
using namespace std;
typedef long long LL;

const int MAXN = 100010;

int sum[MAXN];
int n, k;

int readint() {
    char c = getchar();
    while(!isdigit(c)) c = getchar();
    int res = 0;
    while(isdigit(c)) res = res * 10 + c - '0', c = getchar();
    return res;
}

struct Point {
    int x, y;
    Point() {}
    Point(int x, int y): x(x), y(y) {}
    Point operator - (const Point &rhs) const {
        return Point(x - rhs.x, y - rhs.y);
    }
    double slope() {
        return (double)y / x;
    }
};

LL cross(const Point &a, const Point &b) {
    return (LL)a.x * b.y - (LL)a.y * b.x;
}

LL cross(const Point &o, const Point &a, const Point &b) {
    return cross(a - o, b - o);
}

Point que[MAXN], p;
int head, tail;

double solve() {
    double res = 0;
    head = 0; tail = -1;
    for(int i = k; i <= n; ++i) {
        p = Point(i - k, sum[i - k]);
        while(head < tail && cross(que[tail - 1], que[tail], p) <= 0) --tail;
        que[++tail] = p;

        p = Point(i, sum[i]);
        while(head < tail && cross(que[head], que[head + 1], p) >= 0) ++head;
        res = max(res, (p - que[head]).slope());
    }
    return res;
}

int main() {
    while(scanf("%d%d", &n, &k) != EOF) {
        for(int i = 1; i <= n; ++i) sum[i] = sum[i - 1] + readint();
        /*k = rand() % n + 1;
        srand(clock());
        for(int i = 1; i <= n; ++i) sum[i] = sum[i - 1] + rand() % 2000 + 1;*/
        printf("%.2f\n", solve());
    }
}
