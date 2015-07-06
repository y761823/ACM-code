#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long LL;

const int MAXN = 50010;

struct Point {
    int x, y;
    bool operator < (const Point &rhs) const {
        if(y != rhs.y) return y < rhs.y;
        return x < rhs.x;
    }
};

inline bool Cross(Point &sp, Point &ep, Point &op) {
    return (sp.x - op.x) * (ep.y - op.y) - (ep.x - op.x) * (sp.y - op.y) >= 0;
}

Point p[MAXN];
int n, C;
int stk[MAXN], top;

void Graham_scan() {
    sort(p, p + n);
    top = 1;
    stk[0] = 0; stk[1] = 1;
    if(n < 3) return ;
    for(int i = 2; i < n; ++i) {
        while(top && Cross(p[i], p[stk[top]], p[stk[top - 1]])) --top;
        stk[++top] = i;
    }
    int len = top;
    stk[++top] = n - 2;
    for(int i = n - 3; i >= 0; --i) {
        while(top != len && Cross(p[i], p[stk[top]], p[stk[top - 1]])) --top;
        stk[++top] = i;
    }
}

double ans1, ans2;

void check(Point a, Point b) {
    if(a.x > b.x) swap(a, b);
    if(a.x <= C && C <= b.x) {
        if(a.x == C && b.x == C) {
            ans1 = min(ans1, (double)min(a.y, b.y));
            ans2 = max(ans2, (double)max(a.y, b.y));
        } else {
            double t = ((double)C - a.x) / (b.x - a.x) * (b.y - a.y) + a.y;
            ans1 = min(ans1, t);
            ans2 = max(ans2, t);
        }
    }
}

void solve() {
    stk[++top] = stk[0];
    for(int i = 0; i < top; ++i) {
        check(p[stk[i]], p[stk[i + 1]]);
    }
}

int main() {
    while(scanf("%d%d", &n, &C) != EOF) {
        for(int i = 0; i < n; ++i) scanf("%d", &p[i].x);
        for(int i = 0; i < n; ++i) scanf("%d", &p[i].y);
        if(n == 1) {
            printf("%.3f %.3f\n", (double)p[0].y, (double)p[0].y);
            continue;
        }
        Graham_scan();
        ans1 = 1e12, ans2 = -1e12;
        solve();
        printf("%.3f %.3f\n", ans1, ans2);
    }
}
