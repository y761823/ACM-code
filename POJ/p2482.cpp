#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
typedef long long LL;

const int MAXN = 10010;
const int MAXT = MAXN << 2;
const int INF = 0x3f3f3f3f;

int maxt[MAXT], add[MAXT];

int id(int l, int r) {
    return (l + r) | (l != r);
}
#define x id(l, r)
#define mid ((l + r) >> 1)
#define ll id(l, mid)
#define rr id(mid + 1, r)

void addVal(int l, int r, int v) {
    add[x] += v;
    maxt[x] += v;
}

void pushdown(int l, int r) {
    if(add[x]) {
        addVal(l, mid, add[x]);
        addVal(mid + 1, r, add[x]);
        add[x] = 0;
    }
}

void update(int l, int r) {
    maxt[x] = max(maxt[ll], maxt[rr]);
}

void modify(int l, int r, int a, int b, int v) {
    if(a <= l && r <= b) {
        addVal(l, r, v);
    } else {
        pushdown(l, r);
        if(a <= mid) modify(l, mid, a, b, v);
        if(mid < b) modify(mid + 1, r, a, b, v);
        update(l, r);
    }
}
#undef x

vector<int> xtmp;
int gethash(int x) {
    return lower_bound(xtmp.begin(), xtmp.end(), x) - xtmp.begin();
}

struct Node {
    int x, y, c;
    Node() {}
    Node(int x, int y, int c): x(x), y(y), c(c) {}
    bool operator < (const Node &rhs) const {
        return y < rhs.y;
    }
} arr[MAXN << 1];

int w, h, n, cnt;

int solve() {
    memset(maxt, 0, 2 * xtmp.size() * sizeof(int));
    memset(add, 0, 2 * xtmp.size() * sizeof(int));
    sort(arr, arr + cnt);
    int res = 0, p = 0, rt = id(0, xtmp.size() - 1);
    while(p < cnt) {
        int q = p;
        while(q < cnt && arr[q].y == arr[p].y)
            modify(0, xtmp.size() - 1, gethash(arr[q].x - w + 1), gethash(arr[q].x), arr[q].c), q++;
        p = q;
        res = max(res, maxt[rt]);
    }
    return res;
}

int main() {
    while(scanf("%d%d%d", &n, &w, &h) != EOF) {
        xtmp.clear();
        cnt = 0;
        for(int i = 0, x, y, c; i < n; ++i) {
            scanf("%d%d%d", &x, &y, &c);
            xtmp.push_back(x - w + 1);
            xtmp.push_back(x);

            arr[cnt++] = Node(x, y - h, c);
            arr[cnt++] = Node(x, y, -c);
        }
        sort(xtmp.begin(), xtmp.end());
        xtmp.erase(unique(xtmp.begin(), xtmp.end()), xtmp.end());
        printf("%d\n", solve());
    }
}
