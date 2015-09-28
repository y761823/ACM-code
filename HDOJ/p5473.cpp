#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <complex>
using namespace std;
typedef long long LL;
#define FOR(i, s, t) for(int i = s; i <= t; ++i)

const int MAXN = 210;

typedef complex<int> Point;
#define x real()
#define y imag()

bool cmp_y(const Point &a, const Point &b) {
    if(a.y != b.y) return a.y < b.y;
    return a.x < b.x;
}
void read(Point &p) {
    static int xx, yy;
    scanf("%d%d", &xx, &yy);
    p = Point(xx, yy);
}
LL cross(const Point &a, const Point &b) { // res > 0 means a on right
    return (LL)a.x * b.y - (LL)a.y * b.x;
}
LL cross(const Point &o, const Point &a, const Point &b) { // res < 0 means turn right
    return cross(a - o, b - o);
}

void Graham_scan(Point p[], int n, int stk[], int &top) {//stk[0] = stk[top]
    sort(p, p + n, cmp_y);
    top = 1;
    stk[0] = 0; stk[1] = 1;
    for(int i = 2; i < n; ++i) {
        while(top && cross(p[stk[top - 1]], p[stk[top]], p[i]) <= 0) --top;
        stk[++top] = i;
    }
    int len = top;
    stk[++top] = n - 2;
    for(int i = n - 3; i >= 0; --i) {
        while(top != len && cross(p[stk[top - 1]], p[stk[top]], p[i]) <= 0) --top;
        stk[++top] = i;
    }
}

LL dp[MAXN][MAXN];

LL get_max_area(Point p[], int n, int k, int st) {
    memset(dp, 0, sizeof(dp));
    for(int i = 2; i < n; ++i) {
        for(int j = 3; j <= i + 1 && j <= k; ++j) {
            dp[i][j] = 0;
            for(int pre = j - 2; pre < i; ++pre) {
                dp[i][j] = max(dp[i][j], dp[pre][j - 1] + abs(cross(p[st], p[i + st], p[pre + st])));
            }
        }
    }
    LL res = 0;
    for(int i = k - 1; i < n; ++i)
        res = max(res, dp[i][k]);
    return res;
}

Point p[MAXN], q[MAXN];
int stk[MAXN], top;
int T, n, k;


LL solve() {
    if(k <= 2) return 0;
    Graham_scan(p, n, stk, top);
    if(top <= 2) return 0;
    for(int i = 0; i < top; ++i)
        q[top + i] = q[i] = p[stk[i]];
    k = min(top, k);

    LL res = 0;
    for(int i = 0, cnt = 10 * top / k; i < cnt; ++i) {
        int st = rand() % top;
        res = max(res, get_max_area(q, top, k, st));
    }
    return res;
}
int main() {
    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        scanf("%d%d", &n, &k);
        for(int i = 0; i < n; ++i) read(p[i]);
        printf("Case #%d: %I64d\n", t, solve());
    }
}
