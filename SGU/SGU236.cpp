#include <bits/stdc++.h>
using namespace std;

const int MAXV = 55;
const int MAXE = MAXV * MAXV;
const double EPS = 1e-8;

namespace Bilibili {

struct Edge {
    int u, v, c, t;
    void read() {
        scanf("%d%d%d%d", &u, &v, &c, &t);
    }
} edge[MAXE];
double dis[MAXV];
int pre[MAXV];
int n, m;

int check(double k) {
    for(int i = 1; i <= n; ++i) dis[i] = 0;
    for(int zz = 0; zz <= n; ++zz) {
        for(int i = 0; i < m; ++i) {
            double d = dis[edge[i].u] + (k * edge[i].t - edge[i].c);
            if(d < dis[edge[i].v]) {
                dis[edge[i].v] = d;
                //printf("#debug %d\n", double(dis[u] + cost[p]) < dis[v]);
                pre[edge[i].v] = edge[i].u;
                if(zz == n) return edge[i].v;
            }
        }
    }
    return 0;
}

double mat[MAXV][MAXV];
bool vis[MAXV];
int cnt[MAXV];
int spfa(double k) {
    memset(mat, 0, sizeof(mat));
    memset(vis, 1, sizeof(vis));
    memset(cnt, 0, sizeof(cnt));
    for(int i = 0; i < m; ++i)
        mat[edge[i].u][edge[i].v] = k * edge[i].t - edge[i].c;
    queue<int> que;
    for(int i = 1; i <= n; ++i) dis[i] = 0, que.push(i);
    while(!que.empty()) {
        int u = que.front(); que.pop();
        vis[u] = false;
        for(int v = 1; v <= n; ++v) if(mat[u][v]) {
            double d = dis[u] + mat[u][v];
            if(d < dis[v]) {
                dis[v] = d;
                if(!vis[v]) {
                    vis[v] = true;
                    pre[v] = u;
                    if(++cnt[v] > n) return v;
                    que.push(v);
                }
            }
        }
    }
    return 0;
}

void print_path(int x) {
    memset(vis + 1, 0, n * sizeof(bool));
    while(!vis[x]) {
        vis[x] = true;
        x = pre[x];
    }
    vector<int> ans(1, x);
    int u = pre[x];
    while(u != x) ans.push_back(u), u = pre[u];
    printf("%u\n", ans.size());
    for(vector<int>::reverse_iterator it = ans.rbegin(); it != ans.rend(); ++it)
        printf("%d ", *it);
    puts("");
}

void solve() {
    double l = EPS, r = 101;
    while(l + EPS < r) {
        double mid = (l + r) / 2;
        if(check(mid)) l = mid;
        else r = mid;
    }
    int res = spfa(l); /// 换成check(l)无法AC，原因不明啊。
    if(res == 0) puts("0");
    else print_path(res);
}

void mymain() {
    scanf("%d%d", &n, &m);
    for(int i = 0; i < m; ++i)
        edge[i].read();
    solve();
}

}

int main() {
    Bilibili::mymain();
}
