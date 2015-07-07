#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
typedef long long LL;

const int MAXV = 100010;
const int MAXE = MAXV << 1;
const int INF = 0x3f3f3f3f;

int head[MAXV], ecnt;
int to[MAXE], nxt[MAXE];
int tid[MAXV], eid[MAXV], tree[MAXV];
int n, m, dfs_clock;

void init() {
    memset(head + 1, -1, n * sizeof(int));
    dfs_clock = ecnt = 0;
}

void add_edge(int u, int v) {
    to[ecnt] = v; nxt[ecnt] = head[u]; head[u] = ecnt++;
    to[ecnt] = u; nxt[ecnt] = head[v]; head[v] = ecnt++;
}

void dfs(int u, int f) {
    tid[u] = ++dfs_clock;
    for(int p = head[u]; ~p; p = nxt[p]) {
        int v = to[p];
        if(v != f) dfs(v, u);
    }
    eid[u] = dfs_clock;
}

int lowbit(int x) {
    return x & -x;
}

void modify(int _x, int v) {
    for(int x = _x; x <= n; x += lowbit(x))
        tree[x] += v;
}

int getSum(int _x) {
    int res = 0;
    for(int x = _x; x; x -= lowbit(x))
        res += tree[x];
    return res;
}

int main() {
    scanf("%d", &n);
    init();
    for(int i = 1, u, v; i < n; ++i) {
        scanf("%d%d", &u, &v);
        add_edge(u, v);
    }
    dfs(1, 0);
    for(int i = 1; i <= n; ++i)
        modify(i, 1);

    scanf("%d", &m);
    char op;
    for(int i = 0, x; i < m; ++i) {
        scanf(" %c%d", &op, &x);
        if(op == 'C') modify(tid[x], getSum(tid[x]) - getSum(tid[x] - 1) > 0 ? -1 : 1);
        if(op == 'Q') printf("%d\n", getSum(eid[x]) - getSum(tid[x] - 1));
    }
}
