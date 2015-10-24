#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;
typedef long long LL;
#define FOR(i, s, t) for(int i = s; i <= t; ++i)

const int MAXN = 100010;

struct Point {
    int x, y;
    bool operator == (const Point &rhs) const {
        return x == rhs.x && y == rhs.y;
    }
} p[MAXN];
bool cmp_x(const Point &a, const Point &b) {
    if(a.x != b.x) return a.x < b.x;
    return a.y < b.y;
}
bool cmp_y(const Point &a, const Point &b) {
    if(a.y != b.y) return a.y < b.y;
    return a.x < b.x;
}

struct Operator {
    int x, y, val;
    Operator() {}
    Operator(int x, int y, int val):
        x(x), y(y), val(val) {}
    bool operator < (const Operator &rhs) const {
        return y < rhs.y;
    }
} op[MAXN];
int cnt;

int tree[MAXN];
int n, m;

inline int lowbit(int x) {
    return x & -x;
}

void modify(int x, int val) {
    while(x <= m) {
        tree[x] += val;
        x += lowbit(x);
    }
}

int getsum(int x) {
    int res = 0;
    while(x) {
        res += tree[x];
        x -= lowbit(x);
    }
    return res;
}

int solve() {
    sort(p, p + n, cmp_x);
    int v = 0;
    while(v < n) {
        int u = v;
        while(u + 1 < n && p[u + 1].x == p[v].x) ++u;
        if(v < u) {
            op[cnt++] = Operator(p[v].x, p[v].y, 1);
            op[cnt++] = Operator(p[u].x, p[u].y + 1, -1);
        }
        v = u + 1;
    }
    sort(op, op + cnt);
    sort(p, p + n, cmp_y);
    int a = 0, c = 0, res = n;
    while(a < n) {
        while(c < cnt && op[c].y <= p[a].y) {
            modify(op[c].x, op[c].val);
            c++;
        }
        int b = a;
        while(b + 1 < n && p[b + 1].y == p[a].y) ++b;
        if(a < b) {
            res += getsum(p[b].x) - getsum(p[a].x - 1);
            for(int i = a; i <= b; ++i)
                res -= getsum(p[i].x) - getsum(p[i].x - 1);
        }
        a = b + 1;
    }
    return res;
}

int main() {
    vector<int> table;
    scanf("%d", &n);
    for(int i = 0; i < n; ++i) {
        scanf("%d%d", &p[i].x, &p[i].y);
        table.push_back(p[i].x);
    }
    sort(table.begin(), table.end());
    table.erase(unique(table.begin(), table.end()), table.end());
    m = table.size();
    for(int i = 0; i < n; ++i)
        p[i].x = lower_bound(table.begin(), table.end(), p[i].x) - table.begin() + 1;
    printf("%d\n", solve());
}
