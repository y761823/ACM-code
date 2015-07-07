////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-10-12 21:00:39
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 5016
////Problem Title: 
////Run result: Accept
////Run time:1468MS
////Run memory:9208KB
//////////////////System Comment End//////////////////
#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXV = 100010;
const int MAXE = MAXV << 1;
const int INF = 0x3f3f3f3f;

int head[MAXV], mart[MAXV], ecnt;
int to[MAXE], next[MAXE], cost[MAXE];
int n, m;

void init() {
    memset(head + 1, -1, n * sizeof(int));
    ecnt = 0;
}

void add_edge(int u, int v, int c) {
    to[ecnt] = v; cost[ecnt] = c; next[ecnt] = head[u]; head[u] = ecnt++;
    to[ecnt] = u; cost[ecnt] = c; next[ecnt] = head[v]; head[v] = ecnt++;
}

pair<int, int> dis[MAXV];
int fa[MAXV], q[MAXV], len[MAXV], qcnt;

void dfs_dis(int u, int f) {
    q[qcnt++] = u; fa[u] = f;
    dis[u] = mart[u] ? make_pair(0, u) : make_pair(INF, INF);
    for(int p = head[u]; ~p; p = next[p]) {
        int v = to[p];
        if(v == f) continue;
        len[v] = cost[p];
        dfs_dis(v, u);
        dis[u] = min(dis[u], make_pair(dis[v].first + cost[p], dis[v].second));
    }
}

void get_dis() {
    qcnt = 0;
    dfs_dis(1, 0);
    for(int i = 1; i < qcnt; ++i) {
        int u = q[i];
        dis[u] = min(dis[u], make_pair(dis[fa[u]].first + len[u], dis[fa[u]].second));
    }
}

bool iscut[MAXV];
int size[MAXV], maxsize[MAXV];

void dfs_size(int u, int f) {
    q[qcnt++] = u;
    size[u] = 1; maxsize[u] = 0;
    for(int p = head[u]; ~p; p = next[p]) {
        int v = to[p];
        if(v == f || iscut[v]) continue;
        dfs_size(v, u);
        size[u] += size[v];
        maxsize[u] = max(maxsize[u], size[v]);
    }
}

int get_centre(int st) {
    qcnt = 0;
    dfs_size(st, 0);
    for(int i = 1; i < qcnt; ++i) {
        int v = q[i];
        maxsize[v] = max(maxsize[v], size[st] - size[v]);
    }
    int u = st;
    for(int i = 0; i < qcnt; ++i) {
        int v = q[i];
        if(maxsize[v] < maxsize[u]) u = v;
    }
    return u;
}

void dfs_len(int u, int f, int depth) {
    q[qcnt++] = u;
    len[u] = depth;
    for(int p = head[u]; ~p; p = next[p]) {
        int v = to[p];
        if(v == f || iscut[v]) continue;
        dfs_len(v, u, depth + cost[p]);
    }
}

pair<int, int> dist[MAXV];
int ans[MAXV], dcnt;

void dfs_ans(int st) {
    int r = get_centre(st);
    iscut[r] = true;

    qcnt = 0;
    dfs_len(r, 0, 0);

    dcnt = 0;
    for(int i = 0; i < qcnt; ++i) {
        int v = q[i];
        dist[dcnt++] = make_pair(dis[v].first - len[v], dis[v].second);
    }
    sort(dist, dist + dcnt);
    for(int i = 0; i < qcnt; ++i) {
        int v = q[i];
        ans[v] += dist + dcnt - upper_bound(dist, dist + dcnt, make_pair(len[v], v));
    }

    for(int p = head[r]; ~p; p = next[p]) {
        int u = to[p];
        if(iscut[u]) continue;

        dcnt = qcnt = 0;
        dfs_len(u, r, cost[p]);
        for(int i = 0; i < qcnt; ++i) {
            int v = q[i];
            dist[dcnt++] = make_pair(dis[v].first - len[v], dis[v].second);
        }
        sort(dist, dist + dcnt);
        for(int i = 0; i < qcnt; ++i) {
            int v = q[i];
            ans[v] -= dist + dcnt - upper_bound(dist, dist + dcnt, make_pair(len[v], v));
        }
    }

    for(int p = head[r]; ~p; p = next[p]) {
        int v = to[p];
        if(!iscut[v]) dfs_ans(v);
    }
}

int solve() {
    get_dis();
    memset(iscut + 1, 0, n * sizeof(bool));
    memset(ans + 1, 0, n * sizeof(int));
    dfs_ans(1);
    return *max_element(ans + 1, ans + n + 1);
}

int main() {
    while(scanf("%d", &n) != EOF) {
        init();
        for(int i = 1, u, v, c; i < n; ++i) {
            scanf("%d%d%d", &u, &v, &c);
            add_edge(u, v, c);
        }
        for(int i = 1; i <= n; ++i)
            scanf("%d", &mart[i]);
        printf("%d\n", solve());
    }
}
