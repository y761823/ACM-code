#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;
typedef long long LL;
#define FOR(i, s, t) for(int i = s; i <= t; ++i)

const int MAXN = 100010;

vector<int> sons[MAXN], primes[MAXN];
int pre[MAXN][64], now[MAXN];
int weight[MAXN], ans[MAXN];
int n;

void init_prime(int n = 100000) {
    for(int i = 2; i <= n; ++i) {
        if(!primes[i].empty()) continue;
        primes[i].push_back(i);
        for(int j = i + i; j <= n; j += i)
            primes[j].push_back(i);
    }
}

int dfs_query(size_t dep, int x, int val = 1, int pos = 0, int flag = 1) {
    int v = weight[x];
    if(dep == primes[v].size()) {
        return flag * (now[val] - pre[x][pos]);
    } else {
        return dfs_query(dep + 1, x, val, pos << 1, flag)
            + dfs_query(dep + 1, x, val * primes[v][dep], (pos << 1) | 1, -flag);
    }
}

void dfs_fac(size_t dep, int x, int val = 1, int pos = 0) {
    int v = weight[x];
    if(dep == primes[v].size()) {
        pre[x][pos] = now[val]++;
    } else {
        dfs_fac(dep + 1, x, val, pos << 1);
        dfs_fac(dep + 1, x, val * primes[v][dep], (pos << 1) | 1);
    }
}

void dfs_ans(int u, int f) {
    dfs_fac(0, u);
    for(int v : sons[u]) if(v != f) {
        dfs_ans(v, u);
    }
    ans[u] = dfs_query(0, u);
}

int main() {
    init_prime();
    int kase = 0;
    while(scanf("%d", &n) != EOF) {
        for(int i = 1; i <= n; ++i)
            sons[i].clear();
        for(int i = 1, u, v; i < n; ++i) {
            scanf("%d%d", &u, &v);
            sons[u].push_back(v);
            sons[v].push_back(u);
        }
        for(int i = 1; i <= n; ++i) scanf("%d", &weight[i]);
        memset(now, 0, sizeof(now));
        dfs_ans(1, 0);
        printf("Case #%d:", ++kase);
        for(int i = 1; i <= n; ++i)
            printf(" %d", ans[i]);
        puts("");
    }
}
