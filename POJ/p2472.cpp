#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;
typedef long long LL;

const int MAXN = 110;
const int MAXE = MAXN * MAXN;
const double EPS = 1e-10;

inline int sgn(double x) {
    return (x > EPS) - (x < -EPS);
}

int head[MAXN];
int to[MAXE], next[MAXE];
double cost[MAXE];
int ecnt, n, m;

void init() {
    memset(head, -1, sizeof(head));
    ecnt = 0;
}

void add_edge(int u, int v, double c) {
    to[ecnt] = v; cost[ecnt] = c; next[ecnt] = head[u]; head[u] = ecnt++;
    to[ecnt] = u; cost[ecnt] = c; next[ecnt] = head[v]; head[v] = ecnt++;
    //printf("%d--%d %d\n", u, v, c);
}

double dis[MAXN];
bool inque[MAXN];

double SPFA(int st) {
    for(int i = 1; i <= n; ++i) dis[i] = 0;
    memset(inque, false, sizeof(inque));
    dis[st] = 1; inque[st] = true;
    queue<int> que; que.push(st);
    while(!que.empty()) {
        int u = que.front(); que.pop();
        inque[u] = false;
        for(int p = head[u]; ~p; p = next[p]) {
            int &v = to[p];
            if(sgn(dis[u] * cost[p] - dis[v]) > 0) {
                dis[v] = dis[u] * cost[p];
                if(!inque[v]) {
                    que.push(v);
                    inque[v] = true;
                }
            }
        }
    }
    return dis[n];
}

int main() {
    while(scanf("%d%d", &n, &m) != EOF && n) {
        init();
        while(m--) {
            int u, v, p;
            scanf("%d%d%d", &u, &v, &p);
            add_edge(u, v, p / 100.0);
        }
        printf("%.6f percent\n", 100 * SPFA(1));
    }
}
