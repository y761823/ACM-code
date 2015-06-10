#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXN = 10010;
const int MAXE = 20010;
const int INF = 0x7fff7fff;

int head[MAXN], size[MAXN], maxSize[MAXN];
int list[MAXN], cnt;
bool del[MAXN];
int to[MAXE], next[MAXE], cost[MAXE];
int n, k, ecnt;

void init() {
    memset(head, -1, sizeof(head));
    memset(del, 0, sizeof(del));
    ecnt = 0;
}

void add_edge(int u, int v, int c) {
    to[ecnt] = v; cost[ecnt] = c; next[ecnt] = head[u]; head[u] = ecnt++;
    to[ecnt] = u; cost[ecnt] = c; next[ecnt] = head[v]; head[v] = ecnt++;
}

void dfs1(int u, int f) {
    size[u] = 1;
    maxSize[u] = 0;
    for(int p = head[u]; ~p; p = next[p]) {
        int &v = to[p];
        if(v == f || del[v]) continue;
        dfs1(v, u);
        size[u] += size[v];
        maxSize[u] = max(maxSize[u], size[v]);
    }
    list[cnt++] = u;
}

int get_root(int u, int f) {
    cnt = 0;
    dfs1(u, f);
    int ret, maxr = INF;
    for(int i = 0; i < cnt; ++i) {
        int &x = list[i];
        if(max(maxSize[x], size[u] - size[x]) < maxr) {
            ret = x;
            maxr = max(maxSize[x], size[u] - size[x]);
        }
    }
    return ret;
}

void dfs2(int u, int f, int dis) {
    list[cnt++] = dis;
    for(int p = head[u]; ~p; p = next[p]) {
        int &v = to[p];
        if(v == f || del[v]) continue;
        dfs2(v, u, dis + cost[p]);
    }
}

int calc(int a, int b) {
    int j = b - 1, ret = 0;
    for(int i = a; i < b; ++i) {
        while(list[i] + list[j] > k && i < j) --j;
        ret += j - i;
        if(j == i) break;
    }
    return ret;
}

int ans = 0;

void work(int u, int f) {
    int root = get_root(u, f);
    del[root] = true;
    int last = 0; cnt = 0;
    for(int p = head[root]; ~p; p = next[p]) {
        int &v = to[p];
        if(del[v]) continue;
        dfs2(v, root, cost[p]);
        sort(list + last, list + cnt);
        ans -= calc(last, cnt);
        last = cnt;
    }
    list[cnt++] = 0;
    sort(list, list + cnt);
    ans += calc(0, cnt);
    for(int p = head[root]; ~p; p = next[p]) {
        int &v = to[p];
        if(del[v]) continue;
        work(v, root);
    }
}

int main() {
    while(scanf("%d%d", &n, &k) != EOF) {
        if(n == 0 && k == 0) break;
        init();
        for(int i = 1; i < n; ++i) {
            int u, v, c;
            scanf("%d%d%d", &u, &v, &c);
            add_edge(u, v, c);
        }
        ans = 0;
        work(1, 0);
        printf("%d\n", ans);
    }
}
