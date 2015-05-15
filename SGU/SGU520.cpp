#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int MAXN = 1005;
const int MAXE = 2005;

int n, m, f, ecnt;
int head[MAXN], dis[MAXN];
int to[MAXE], next[MAXE];

void add_edge(int u, int v) {
    to[ecnt] = v; next[ecnt] = head[u]; head[u] = ecnt++;
    to[ecnt] = u; next[ecnt] = head[v]; head[v] = ecnt++;
}

void bfs() {
    queue<int> que; que.push(1);
    dis[1] = 1;
    while(!que.empty()) {
        int u = que.front(); que.pop();
        for(int p = head[u]; p; p = next[p]) {
            int &v = to[p];
            if(!dis[v]) {
                dis[v] = dis[u] + 1;
                que.push(v);
            }
        }
    }
}

bool vis[MAXN];
int win[MAXN];

int dfs(int u) {
    if(win[u] != -1) return win[u];
    for(int p = head[u]; p; p = next[p]) {
        int &v = to[p];
        if(dis[v] == dis[u] + 1) {
            if(dis[u] & 1) {
                if(dfs(v)) return win[u] = 1;
            }
            else if(!dfs(v)) return win[u] = 0;
        }
    }
    return win[u] = !(dis[u] & 1);
}

int main() {
    scanf("%d%d", &n, &m);
    ecnt = 1;
    while(m--) {
        int u, v;
        scanf("%d%d", &u, &v);
        add_edge(u, v);
    }
    bfs();
    memset(win, -1, sizeof(win));
    if(dfs(1)) puts("Vladimir");
    else puts("Nikolay");
}
