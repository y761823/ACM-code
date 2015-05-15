/*
ID: y7618231
PROG: picture
LANG: C++11
*/
#ifdef OYK_JUDGE
#define longformat "%I64d"
#else
#define longformat "%lld"
#endif // OYK_JUDGE

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <numeric>
#include <set>
#include <deque>
#include <queue>
#include <cctype>
using namespace std;
typedef long long LL;
#define REP(i, n) for(int i = 0; i < n; ++i)
#define FOR(i, s, t) for(int i = s; i <= t; ++i)

const int MAXN = 5010;
const int MAXT = MAXN << 4;
const int INF = 0x3f3f3f3f;

vector<int> tmp;

int get_hash(int x) {
    return lower_bound(tmp.begin(), tmp.end(), x) - tmp.begin();
}

struct Segment {
    int l, r, c, flag;
    int length() {
        return r - l;
    }
    bool operator < (const Segment &rhs) const {
        if(c != rhs.c) return c < rhs.c;
        return flag > rhs.flag;
    }
};

struct Rect {
    int x1, x2, y1, y2;
    void read() {
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
    }
    void swap() {
        std::swap(x1, y1);
        std::swap(x2, y2);
    }
};

#define ll (x << 1)
#define rr (ll | 1)
#define mid ((l + r) >> 1)
int sum[MAXT], cover[MAXT];

void update(int x, int l, int r) {
    if(cover[x]) sum[x] = tmp[r] - tmp[l];
    else sum[x] = sum[ll] + sum[rr];
}

void modify(int x, int l, int r, int a, int b, int val) {
    if(a <= l && r <= b) {
        cover[x] += val;
    } else {
        if(a < mid) modify(ll, l, mid, a, b, val);
        if(mid < b) modify(rr, mid, r, a, b, val);
    }
    update(x, l, r);
}

int query(int x, int l, int r, int a, int b) {
    if(a <= l && r <= b) {
        return sum[x];
    } else if(cover[x]) {
        return tmp[min(r, b)] - tmp[max(l, a)];
    } else {
        int res = 0;
        if(a < mid) res += query(ll, l, mid, a, b);
        if(mid < b) res += query(rr, mid, r, a, b);
        return res;
    }
}

Segment seg[MAXN << 1];
Rect rect[MAXN];
int n, cnt;

void init() {
    tmp.clear();
    for(int i = 0; i < n; ++i) {
        tmp.push_back(rect[i].x1);
        tmp.push_back(rect[i].x2);
    }
    sort(tmp.begin(), tmp.end());
    tmp.erase(unique(tmp.begin(), tmp.end()), tmp.end());

    cnt = 0;
    for(int i = 0; i < n; ++i) {
        seg[cnt++] = {rect[i].x1, rect[i].x2, rect[i].y1, 1};
        seg[cnt++] = {rect[i].x1, rect[i].x2, rect[i].y2, -1};
    }
    sort(seg, seg + cnt);
}

LL solve() {
    init();
    LL res = 0;
    int m = tmp.size();
    for(int i = 0; i < cnt; ++i) {
        int l = get_hash(seg[i].l), r = get_hash(seg[i].r);
        if(seg[i].flag == 1) res += seg[i].length() - query(1, 0, m - 1, l, r);
        modify(1, 0, m - 1, l, r, seg[i].flag);
    }
    return res * 2;
}

int main() {
#ifndef OYK_JUDGE
    freopen("picture.in", "r", stdin); freopen("picture.out", "w", stdout);
#endif // OYK_JUDGE
    scanf("%d", &n);
    for(int i = 0; i < n; ++i) rect[i].read();
    LL res = solve();
    for(int i = 0; i < n; ++i) rect[i].swap();
    res += solve();
    printf(longformat "\n", res);
}
