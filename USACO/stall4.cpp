/*
ID: y7618231
PROG: stall4
LANG: C++11
*/
#ifdef OYK_JUDGE
#define longformat "%I64d"
#else
#define longformat "%lld"
#endif // OYK_JUDGE

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long LL;
#define REP(i, n) for(int i = 0; i < n; ++i)
#define FOR(i, s, t) for(int i = s; i <= t; ++i)

const int MAXV = 210;
const int INF = 0x3f3f3f3f;

vector<int> edge[MAXV];

bool vis[MAXV];
int link[MAXV];
int n, m;

bool dfs(int u) {
    for(int v : edge[u]) if(!vis[v]) {//c++11
        vis[v] = true;
        if(!link[v] || dfs(link[v])) {
            link[v] = u;
            return true;
        }
    }
    return false;
}

int hungary() {
    int res = 0;
    for(int i = 1; i <= n; ++i) {
        memset(vis + 1, 0, m * sizeof(bool));
        res += dfs(i);
    }
    return res;
}

int main() {
#ifndef OYK_JUDGE
    freopen("stall4.in", "r", stdin); freopen("stall4.out", "w", stdout);
#endif // OYK_JUDGE
    scanf("%d%d", &n, &m);
    FOR(i, 1, n) {
        int a, b;
        scanf("%d", &a);
        while(a--) scanf("%d", &b), edge[i].push_back(b);
    }
    printf("%d\n", hungary());
}
