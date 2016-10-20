#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <set>
#include <queue>

const int MAXV = 200010;
const int MAXE = 20010 * 2;

int head[MAXV], ecnt;
int to[MAXE], next[MAXE];
int dis[MAXV];
int n, m, T, s;

void init() {
    memset(head, -1, n * sizeof(int));
    ecnt = 0;
}

void add_edge(int u, int v) {
    to[ecnt] = v; next[ecnt] = head[u]; head[u] = ecnt++;
    to[ecnt] = u; next[ecnt] = head[v]; head[v] = ecnt++;
}

void solve() {
    memset(dis, -1, n * sizeof(int));
    std::set<int> unknow;
    for(int i = 0; i < n; ++i)
        unknow.insert(i);

    std::queue<int> que;
    que.push(s); dis[s] = 0; unknow.erase(s);

    while(!que.empty()) {
        int u = que.front(); que.pop();
        std::set<int> unlink;
        for(int p = head[u]; ~p; p = next[p]) {
            int v = to[p];
            if(unknow.find(v) != unknow.end()) {
                unknow.erase(v);
                unlink.insert(v);
            }
        }
        for(int v : unknow)
            dis[v] = dis[u] + 1, que.push(v);
        unknow.swap(unlink);
    }

    bool first = true;
    for(int i = 0; i < n; ++i) {
        if(i == s) continue;
        if(!first) putchar(' ');
        else first = false;
        printf("%d", dis[i]);
    }
    puts("");
}

int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &m);
        init();
        for(int i = 0, a, b; i < m; ++i) {
            scanf("%d%d", &a, &b);
            add_edge(a - 1, b - 1);
        }
        scanf("%d", &s);
        s--;
        solve();
    }
}
