/*
ID: y7618231
PROG: tour
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
#include <unordered_map>
using namespace std;
typedef long long LL;
#define REP(i, n) for(int i = 0; i < n; ++i)
#define FOR(i, s, t) for(int i = s; i <= t; ++i)

const int MAXN = 110;
const int MAXV = MAXN << 1;
const int INF = 0x3f3f3f3f;
const int MOD = 1000000007;

struct SPFA_COST_FLOW {
    int head[MAXV], ecnt;
    vector<int> to, next, flow, cost;
    int n, st, ed;

    void init(int n) {
        this->n = n;
        memset(head + 1, -1, n * sizeof(int));
        ecnt = 0;
    }

    void add_edge(int u, int v, int f, int c) {
        to.push_back(v); flow.push_back(f); cost.push_back(c); next.push_back(head[u]); head[u] = ecnt++;
        to.push_back(u); flow.push_back(0); cost.push_back(-c); next.push_back(head[v]); head[v] = ecnt++;
    }

    int pre[MAXV], dis[MAXV];

    bool spfa() {
        priority_queue<pair<int, int>> que;
        memset(dis + 1, -1, n * sizeof(int));
        que.push(make_pair(dis[st] = 0, st));
        while(!que.empty()) {
            auto tmp = que.top(); que.pop();
            int d = -tmp.first, u = tmp.second;
            if(dis[u] != d) continue;
            for(int p = head[u]; ~p; p = next[p]) {
                int v = to[p];
                if(flow[p] && d + cost[p] > dis[v]) {
                    pre[v] = p;
                    dis[v] = d + cost[p];
                    que.push(make_pair(-dis[v], v));
                }
            }
        }
        return dis[ed] >= 0;
    }

    int maxcost, maxflow;

    void run(int ss, int tt) {
        st = ss, ed = tt;
        maxcost = maxflow = 0;
        while(spfa()) {
            int u = ed;
            while(u != st) {
                flow[pre[u]] -= 1;
                flow[pre[u] ^ 1] += 1;
                u = to[pre[u] ^ 1];
            }
            maxflow += 1;
            maxcost += dis[ed];
        }
    }
} G;

unordered_map<string, int> mymap;
char s[MAXN];
int n, m;

int main() {
#ifndef OYK_JUDGE
    freopen("tour.in", "r", stdin); freopen("tour.out", "w", stdout);
#endif // OYK_JUDGE
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; ++i) {
        scanf("%s", s);
        mymap[s] = i;
    }
    G.init(n << 1);
    for(int i = 1; i <= n; ++i) {
        int cap = 1 + (i == 1 || i == n);
        G.add_edge(i, i + n, cap, 1);
    }
    for(int i = 0, u, v; i < m; ++i) {
        scanf("%s", s); u = mymap[s];
        scanf("%s", s); v = mymap[s];
        if(u > v) swap(u, v);
        G.add_edge(u + n, v, 1, 0);
    }
    G.run(1, n + n);
    if(G.maxflow != 2) puts("1");
    else printf("%d\n", G.maxcost - 2);
}
