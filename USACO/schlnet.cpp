/*
ID: y7618231
PROG: schlnet
LANG: C++11
*/
#ifdef OYK_JUDGE
#define longformat "%I64d"
#else
#define longformat "%lld"
#endif // OYK_JUDGE

#include <vector>
#include <algorithm>
#include <iostream>
#include <queue>
#include <cstdio>
#include <cstring>
#include <functional>
#include <numeric>
#include <set>
using namespace std;
typedef long long LL;
#define REP(i, n) for(int i = 0; i < n; ++i)
#define REPr(i, n) for(int i = n - 1; i >= 0; --i)
#define FOR(i, s, t) for(int i = s; i <= t; ++i)
#define FORr(i, s, t) for(int i = t; i >= s; --i)

const int MAXN = 110;
const int INF = 0x3f3f3f3f;
const int MOD = 1000000007;

bool mat[MAXN][MAXN];
int n;

void floyd() {
    FOR(k, 1, n) FOR(i, 1, n) FOR(j, 1, n)
        if(mat[i][k] && mat[k][j]) mat[i][j] = true;
}

bool vis[MAXN];
int fa[MAXN];
int indeg[MAXN], outdeg[MAXN];

int find_set(int x) {
    return fa[x] == x ? x : fa[x] = find_set(fa[x]);
}

void merge(int x, int y) {
    int fx = find_set(x), fy = find_set(y);
    if(fx != fy) fa[fx] = fy;
}

void solve() {
    iota(fa + 1, fa + n + 1, 1);
    FOR(i, 1, n) FOR(j, 1, n)
        if(mat[i][j] && mat[j][i]) merge(i, j);
    FOR(i, 1, n) FOR(j, 1, n) {
        int x = find_set(i), y = find_set(j);
        if(x != y) {
            if(mat[i][j]) outdeg[x]++, indeg[y]++;
            if(mat[j][i]) outdeg[y]++, indeg[x]++;
        }
    }

    int inzero = 0, outzero = 0;
    FOR(i, 1, n) {
        int x = find_set(i);
        if(vis[x]) continue;
        vis[x] = true;
        inzero += (indeg[x] == 0);
        outzero += (outdeg[x] == 0);
    }

    bool flag = true;
    FOR(i, 2, n)
        if(find_set(1) != find_set(i)) flag = false;
    if(flag) puts("1\n0");
    else printf("%d\n%d\n", inzero, max(inzero, outzero));
}

int main() {
#ifndef OYK_JUDGE
    freopen("schlnet.in", "r", stdin); freopen("schlnet.out", "w", stdout);
#endif // OYK_JUDGE
    scanf("%d", &n);
    FOR(i, 1, n) mat[i][i] = true;
    for(int u = 1, v; u <= n; ++u) {
        scanf("%d", &v);
        while(v != 0) {
            mat[u][v] = true;
            scanf("%d", &v);
        }
    }
    floyd();
    solve();
}
