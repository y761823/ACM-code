////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2013-09-11 19:03:39
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 4725
////Problem Title: 
////Run result: Accept
////Run time:343MS
////Run memory:10968KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
typedef pair<int, int> PII;

const int MAXN = 300010;
const int MAXE = MAXN * 2;

int head[MAXN];
int to[MAXE], next[MAXE], cost[MAXE];
int n, m, ecnt, lcnt, c;

void init() {
    memset(head, 0, sizeof(head));
    ecnt = lcnt = 1;
}

inline void add_edge(int u, int v, int c) {
    to[ecnt] = v; cost[ecnt] = c; next[ecnt] = head[u]; head[u] = ecnt++;
}

int dis[MAXN];
int lay[MAXN];
bool vis[MAXN];

void Dijkstra(int st, int ed) {
    memset(dis, 0x7f, sizeof(dis));
    memset(vis, 0, sizeof(vis));
    priority_queue<PII> que; que.push(make_pair(0, st));
    dis[st] = 0;
    while(!que.empty()) {
        int u = que.top().second; que.pop();
        if(vis[u]) continue;
        if(u == ed) return ;
        vis[u] = true;
        for(int p = head[u]; p; p = next[p]) {
            int &v = to[p];
            if(dis[v] > dis[u] + cost[p]) {
                dis[v] = dis[u] + cost[p];
                que.push(make_pair(-dis[v], v));
            }
        }
    }
}

int T;

inline int readint() {
    char c = getchar();
    while(!isdigit(c)) c = getchar();
    int ret = 0;
    while(isdigit(c)) ret = ret * 10 + c - '0', c = getchar();
    return ret;
}

int main() {
    T = readint();
    for(int t = 1; t <= T; ++t) {
        n = readint(), m = readint(), c = readint();
        init();
        for(int i = 1; i <= n; ++i) {
            lay[i] = readint();
            add_edge(i, n + 2 * lay[i] - 1, 0);
            add_edge(n + 2 * lay[i], i, 0);
        }
        for(int i = 1; i < n; ++i) {
            add_edge(n + 2 * i - 1, n + 2 * (i + 1), c);
            add_edge(n + 2 * (i + 1) - 1, n + 2 * i, c);
        }
        int u, v, w;
        while(m--) {
            //scanf("%d%d%d", &u, &v, &w);
            u = readint(), v = readint(), w = readint();
            add_edge(u, v, w);
            add_edge(v, u, w);
        }
        Dijkstra(1, n);
        if(dis[n] == 0x7f7f7f7f) dis[n] = -1;
        printf("Case #%d: %d\n", t, dis[n]);
    }
}
