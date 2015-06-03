#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <cmath>
using namespace std;
typedef long long LL;

struct Point {
    int x, y;
    Point() {}
    Point(int x, int y): x(x), y(y) {}
    Point operator - (const Point &rhs) const {
        return Point(x - rhs.x, y - rhs.y);
    }
    double ang() const {
        return atan2(y, x);
    }
    bool type() const {
        if(y != 0) return y > 0;
        return x < 0;
    }
};

LL cross(const Point &a, const Point &b) {
    return (LL)a.x * b.y - (LL)a.y * b.x;
}

const int MAXN = 3010;

Point p[MAXN], v[MAXN << 1];
int n, T;

bool cmp(const Point &a, const Point &b) {
    if(a.type() != b.type()) return a.type() < b.type();
    return cross(a, b) > 0;
}

void solve(int n) {
    for(int i = 1; i < n; ++i)
        v[i - 1] = p[i] - p[0];
    n--;
    sort(v, v + n, cmp);
    copy(v, v + n, v + n);
    int res = 0;
    for(int i = 0, j = 0; i < n; ++i) {
        if(i == j) j++;
        while(j < i + n && cross(v[i], v[j]) >= 0) ++j;
        res = max(res, j - i);
    }
    printf("%d\n", n - res);
}

int main() {
    freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout);
    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        scanf("%d", &n);
        for(int i = 0; i < n; ++i)
            scanf("%d%d", &p[i].x, &p[i].y);
        printf("Case #%d:\n", t);
        for(int i = 0; i < n; ++i) {
            swap(p[0], p[i]);
            solve(n);
            swap(p[0], p[i]);
        }
    }
}
