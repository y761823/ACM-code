#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int MAXV = 30010;
const int MAXE = MAXV << 1;

namespace Bilibili {

int head[MAXV], ecnt;
int to[MAXE], next[MAXE];
int n, k;

void init() {
    memset(head + 1, -1, n * sizeof(int));
    ecnt = 0;
}

void add_edge(int u, int v) {
    to[ecnt] = v; next[ecnt] = head[u]; head[u] = ecnt++;
    to[ecnt] = u; next[ecnt] = head[v]; head[v] = ecnt++;
}

int dep[MAXV], fa[MAXV], dis[MAXV];

void pre_dfs(int u, int f, int depth) {
    dep[u] = depth;
    fa[u] = f;
    for(int p = head[u]; ~p; p = next[p]) {
        int v = to[p];
        if(v != f) pre_dfs(v, u, depth + 1);
    }
}

void cover(int u, int d) {
    if(d > k || d >= dis[u]) return ;
    dis[u] = d;
    for(int p = head[u]; ~p; p = next[p])
        cover(to[p], d + 1);
}

int get_xFa(int u, int x) {
    while(x-- && fa[u]) u = fa[u];
    return u;
}

vector<int> ans;

void solve() {
    pre_dfs(1, 0, 0);
    vector<pair<int, int> > order;
    for(int i = 1; i <= n; ++i) order.push_back(make_pair(dep[i], i));
    sort(order.begin(), order.end(), greater<pair<int, int> >());

    memset(dis + 1, 0x3f, n * sizeof(int));
    for(size_t it = 0; it < order.size(); ++it) {
        int u = order[it].second;
        if(dis[u] > k) {
            ans.push_back(u = get_xFa(u, k));
            cover(u, 0);
        }
    }
}

void mymain() {
    scanf("%d%d", &n, &k);
    init();
    for(int i = 1, u, v; i < n; ++i) {
        scanf("%d%d", &u, &v);
        add_edge(u, v);
    }
    solve();
    printf("%u\n", ans.size());
    for(size_t i = 0; i < ans.size(); ++i)
        printf("%d ", ans[i]);
    puts("");
}

}

int main() {
    Bilibili::mymain();
}
