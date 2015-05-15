#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
typedef long long LL;
#define foreach(x, vec) for(__typeof(vec.begin()) x = vec.begin(); x != vec.end(); ++x)

const int MAXN = 110;
const int MAXK = 1010;
const int MOD = 1000000007;

LL dp[MAXN][2];
vector<int> adj[MAXN], vec[MAXN];
int T, n, k;

int power(LL x, int p) {
    int res = 1;
    while(p) {
        if(p & 1) res = res * x % MOD;
        x = x * x % MOD;
        p >>= 1;
    }
    return res;
}

void init() {
    for(int i = 0; i < n; ++i) {
        adj[i].clear();
        vec[i].clear();
    }
}

void add_edge(int u, int v) {
    adj[u].push_back(v);
    vec[v].push_back(u);
}

int vis[MAXN];
int del[MAXN], root, cnt_r;
bool dfs1(int u, bool flag) {
    if(flag && u == root) return true;
    if(vis[u]) return false;
    vis[u] = true;
    foreach(v, vec[u]) if(dfs1(*v, true)) {
        cnt_r++;
        return true;
    }
    return false;
}

int dfs2(int u, bool flag) {
    if(flag && u == root) return 0;
    del[u] = true;
    int res = 1;
    foreach(v, adj[u]) res += dfs2(*v, true);
    return res;
}

int solve() {
    dp[1][1] = k; dp[1][0] = 0;
    for(int i = 2; i <= n; ++i) {
        dp[i][1] = dp[i - 1][0];
        dp[i][0] = ((k - 1) * dp[i - 1][1] + (k - 2) * dp[i - 1][0]) % MOD;
    }

    memset(del, 0, n * sizeof(int));
    int res = 1;
    for(int i = 0; i < n; ++i) if(!del[i]) {
        root = i;
        cnt_r = 0;
        memset(vis, 0, n * sizeof(int));
        if(dfs1(i, false)) {
            int cnt = dfs2(i, false);
            LL tmp = dp[cnt_r][0];
            if(cnt_r < cnt) tmp = tmp * power(k - 1, cnt - cnt_r) % MOD;
            res = res * tmp % MOD;
        }
    }
    return res;
}

int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &k);
        init();
        for(int i = 0, c; i < n; ++i) {
            scanf("%d", &c);
            add_edge(c, i);
        }
        printf("%d\n", solve());
    }
}