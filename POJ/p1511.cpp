#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;
typedef long long LL;

const int MAXV = 1000010;
const int MAXE = MAXV;

int n, m, T;

struct Graph {
    int head[MAXV];
    LL dis[MAXV];
    int to[MAXE], next[MAXE];
    LL cost[MAXE];
    bool vis[MAXV];
    int ecnt;

    void init() {
        memset(head, -1, sizeof(head));
        ecnt = 0;
    }

    void add_edge(int u, int v, LL c) {
        to[ecnt] = v; cost[ecnt] = c; next[ecnt] = head[u]; head[u] = ecnt++;
    }

    LL SPFA(int st) {
        memset(vis, 0, sizeof(vis));
        memset(dis, 0x3f, sizeof(dis));
        queue<int> que;
        que.push(st); dis[st] = 0;
        while(!que.empty()) {
            int u = que.front(); que.pop();
            vis[u] = false;
            for(int p = head[u]; ~p; p = next[p]) {
                int &v = to[p];
                if(dis[u] + cost[p] < dis[v]) {
                    dis[v] = dis[u] + cost[p];
                    if(!vis[v]) {
                        vis[v] = true;
                        que.push(v);
                    }
                }
            }
        }

        LL ret = 0;
        for(int i = 1; i <= n; ++i) ret += dis[i];
        return ret;
    }
} A, B;

int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &m);
        A.init();
        B.init();
        while(m--) {
            int u, v, c;
            scanf("%d%d%d", &u, &v, &c);
            A.add_edge(u, v, c);
            B.add_edge(v, u, c);
        }
        cout<<(A.SPFA(1) + B.SPFA(1))<<endl;
    }
}
