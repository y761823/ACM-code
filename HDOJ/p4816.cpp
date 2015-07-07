////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-08-08 23:00:04
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 4816
////Problem Title: 
////Run result: Accept
////Run time:2390MS
////Run memory:1900KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
typedef long double LDB;

const int MAXN = 200010;
const LDB EPS = 1e-6;

inline int sgn(LDB x) {
    return (x > EPS) - (x < -EPS);
}

int x[MAXN], y[MAXN];
int n, d, L, T;

struct Game {
    LDB a, b, c;
    Game() {}
    Game(LDB a, LDB b, LDB c): a(a), b(b), c(c) {}
    Game operator - (const Game &rhs) const {
        return Game(a - rhs.a, b - rhs.b, c - rhs.c);
    }
    LDB val_at(LDB x) {
        return a * x * x + b * x + c;
    }
    LDB max_val(LDB l, LDB r) {
        LDB res = max(val_at(l), val_at(r));
        if(sgn(a) < 0) {
            LDB t = - b / 2 / a;
            if(sgn(l - t) <= 0 && sgn(t - r) <= 0)
                res = val_at(t);
        }
        return res;
    }
};

Game get(int pos, LDB v = 0.0) {
    LDB k = LDB(y[pos + 1] - y[pos]) / (x[pos + 1] - x[pos]);
    LDB t = y[pos] - k * x[pos];
    LDB a = k / 2, b = t, c = -((k / 2) * x[pos] + t) * x[pos];
    return Game(a, 2 * v * a + b, a * v * v + b * v + c);
}

LDB area(int pos) {
    return (y[pos] + y[pos + 1]) / 2.0 * (x[pos + 1] - x[pos]);
}

LDB solve() {
    if(d == 0) {
        int res = 0;
        for(int i = 1; i <= n; ++i) res = max(res, y[i]);
        return res;
    }
    LDB nowx = 0, res = 0, s = 0;
    int l = 1, r = 1;
    while(r < n && x[r + 1] <= d)
        s += area(r++);
    if(r == n) res = s;
    while(r < n) {
        LDB minx = min(x[l + 1] - nowx, x[r + 1] - nowx - d);
        res = max(res, s + (get(r, d) - get(l)).max_val(nowx, nowx + minx));
        nowx += minx;
        if(sgn(x[l + 1] - nowx) == 0) s -= area(l++), nowx = x[l];
        if(sgn(x[r + 1] - nowx - d) == 0) s += area(r++), nowx = x[r] - d;
    }
    return res / d;
}

int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &L);
        for(int i = 1; i <= n; ++i) scanf("%d%d", &x[i], &y[i]);
        x[n + 1] = x[n];
        scanf("%d", &d); d <<= 1;
        printf("%.3f\n", (double)solve());
    }
}
