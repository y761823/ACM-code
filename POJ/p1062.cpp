#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;

const int MAXV = 110;
const int MAXE = MAXV * MAXV;

int head[MAXV], dis[MAXV * MAXV * MAXV], level[MAXV], val[MAXV];
int to[MAXE], next[MAXE], cost[MAXE];
int n, m, ecnt;

void init() {
    memset(head, 255, sizeof(head));
    ecnt = 0;
}

void add_edge(int u, int v, int c) {
    to[ecnt] = v; cost[ecnt] = c; next[ecnt] = head[u]; head[u] = ecnt++;
}

int encode(int up, int down, int pos) {
    return up * 10000 + down * 100 + pos;
}

void decode(int &up, int &down, int &pos, int val) {
    pos = val % 100;
    val /= 100;
    down = val % 100;
    val /= 100;
    up = val;
}

int dijkstra(int st, int ed) {
    priority_queue<pair<int, int > > que;
    memset(dis, 0x3f, sizeof(dis));
    for(int i = 1; i <= n; ++i) {
        int x = encode(i, i, i);
        dis[x] = val[i];
        que.push(make_pair(-dis[x], x));
    }
    while(!que.empty()) {
        int d = -que.top().first, x = que.top().second; que.pop();
        if(d != dis[x]) continue;
        int up, down, u;
        decode(up, down, u, x);
        for(int p = head[u]; ~p; p = next[p]) {
            int &v = to[p];
            if(level[up] - m <= level[v] && level[v] <= level[down] + m) {
                int new_up = level[up] > level[v] ? up : v;
                int new_down = level[down] < level[v] ? down : v;
                int y = encode(new_up, new_down, v);
                if(d + cost[p] < dis[y]) {
                    dis[y] = d + cost[p];
                    que.push(make_pair(-dis[y], y));
                }
            }
        }
    }
    int ans = val[1];
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= n; ++j) ans = min(ans, dis[encode(i, j, 1)]);
    return ans;
}

int main() {
    scanf("%d%d", &m, &n);
    init();
    for(int i = 1; i <= n; ++i) {
        int x;
        scanf("%d%d%d", &val[i], &level[i], &x);
        while(x--) {
            int v, c;
            scanf("%d%d", &v, &c);
            add_edge(v, i, c);
        }
    }
    printf("%d\n", dijkstra(0, 1));
}
