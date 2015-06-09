#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;
typedef long long LL;

const int MAXN = 100010;

vector<LL> ans;
LL maxval[MAXN];
int val[MAXN], sson[MAXN];
vector<int> adj[MAXN];
int T, n, k;

void init() {
    for(int i = 1; i <= n; ++i)
        adj[i].clear();
}

void add_edge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
}

void dfs(int u, int f) {
    sson[u] = maxval[u] = 0;
    for(int v : adj[u]) if(v != f) {
        dfs(v, u);
        if(maxval[v] > maxval[u]) {
            maxval[u] = maxval[v];
            sson[u] = v;
        }
    }
    maxval[u] += val[u];
    for(int v : adj[u]) if(v != f && v != sson[u])
        ans.push_back(maxval[v]);
}

LL solve() {
    ans.clear();
    dfs(1, 0);
    ans.push_back(maxval[1]);

    k = min(k, (int)ans.size());
    nth_element(ans.begin(), ans.begin() + k, ans.end(), greater<LL>());
    return accumulate(ans.begin(), ans.begin() + k, 0LL);
}

int main() {
    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        scanf("%d%d", &n, &k);
        for(int i = 1; i <= n; ++i) scanf("%d", &val[i]);
        init();
        for(int i = 1, a, b; i < n; ++i) {
            scanf("%d%d", &a, &b);
            add_edge(a, b);
        }
        printf("Case #%d: %I64d\n", t, solve());
    }
}
