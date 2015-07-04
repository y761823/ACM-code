#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
typedef long long LL;

const int MAXV = 1010;
const int MAXE = 200010;

int head[MAXV], ecnt;
int to[MAXE], nxt[MAXE], cost[MAXE];
int n, m;

void init() {
    memset(head + 1, -1, n * sizeof(int));
    ecnt = 0;
}

void add_edge(int u, int v, int c) {
    to[ecnt] = v; cost[ecnt] = c; nxt[ecnt] = head[u]; head[u] = ecnt++;
}

int dis[MAXV], icnt[MAXV];
bool inque[MAXV];

bool spfa() {
    queue<int> que;
    for(int i = 1; i <= n; ++i) {
        dis[i] = icnt[i] = 0;
        que.push(i);
        inque[i] = true;
    }
    while(!que.empty()) {
        int u = que.front(); que.pop();
        inque[u] = false;
        for(int p = head[u]; ~p; p = nxt[p]) {
            int v = to[p];
            if(dis[v] > dis[u] + cost[p]) {
                dis[v] = dis[u] + cost[p];
                if(!inque[v]) {
                    que.push(v);
                    inque[v] = true;
                    if(++icnt[v] >= n) return false;
                }
            }
        }
    }
    return true;
}

int main() {
    while(scanf("%d%d", &n, &m) != EOF) {
        init();
        char op; int a, b, x;
        for(int i = 0; i < m; ++i) {
            scanf(" %c%d%d", &op, &a, &b);
            if(op == 'P') {
                scanf("%d", &x);
                add_edge(a, b, x);
                add_edge(b, a, -x);
            } else {
                add_edge(b, a, -1);
            }
        }
        puts(spfa() ? "Reliable" : "Unreliable");
    }
}
