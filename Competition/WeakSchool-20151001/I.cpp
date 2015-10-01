#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;
typedef long long LL;
#define FOR(i, s, t) for(int i = s; i <= t; ++i)

const int MAXV = 100010;
const int MAXE = 1000010;

int head[MAXV], ecnt;
int to[MAXE], nxt[MAXE];
int n, m, a, b;

void init() {
    memset(head + 1, -1, n * sizeof(int));
    ecnt = 0;
}

void add_edge(int u, int v) {
    to[ecnt] = v; nxt[ecnt] = head[u]; head[u] = ecnt++;
    to[ecnt] = u; nxt[ecnt] = head[v]; head[v] = ecnt++;
}

int dis[MAXV];

int solvea() {
    fill(dis + 1, dis + n + 1, b);
    dis[1] = 0;

    queue<int> que; que.push(1);
    while(!que.empty()) {
        int u = que.front(); que.pop();
        for(int p = head[u]; ~p; p = nxt[p]) {
            int v = to[p];
            if(dis[u] + a < dis[v]) {
                dis[v] = dis[u] + a;
                que.push(v);
            }
        }
    }
    return dis[n];
}

int cnt[MAXV];

int solveb() {
    fill(dis + 1, dis + n + 1, a);
    dis[1] = 0;

    priority_queue<pair<int, int> > que;
    memset(cnt + 1, 0, n * sizeof(int));
    for(int p = head[1]; ~p; p = nxt[p])
        cnt[to[p]]++;
    for(int i = 2; i <= n; ++i)
        que.push(make_pair(-cnt[i], i));
    int viscnt = 1, d = b;

    while(!que.empty() && d < a) {
        int upper = viscnt;
        while(!que.empty() && -que.top().first < upper) {
            int c = -que.top().first, u = que.top().second; que.pop();
            if(cnt[u] != c) continue;
            viscnt++;
            dis[u] = d;
            for(int p = head[u]; ~p; p = nxt[p]) {
                int v = to[p];
                if(dis[v] == a && cnt[v] < upper) {
                    cnt[v]++;
                    que.push(make_pair(-cnt[v], v));
                }
            }
        }
        d += b;
        if(viscnt == upper) break;
    }
    return dis[n];
}

int main() {
    while(scanf("%d%d%d%d", &n, &m, &a, &b) != EOF) {
        init();
        for(int i = 0, u, v; i < m; ++i) {
            scanf("%d%d", &u, &v);
            add_edge(u, v);
        }
        if(a < b) printf("%d\n", solvea());
        if(a == b) printf("%d\n", a);
        if(a > b) printf("%d\n", solveb());
    }
}
