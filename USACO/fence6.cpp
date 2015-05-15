/*
ID: y7618231
PROG: fence6
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
#include <map>
using namespace std;
typedef long long LL;
#define REP(i, n) for(int i = 0; i < n; ++i)
#define FOR(i, s, t) for(int i = s; i <= t; ++i)

const int MAXN = 110;

vector<int> L[MAXN], R[MAXN];
int mat[MAXN][MAXN];
int m;

void solve() {
    int res = 0x3f3f3f3f;
    FOR(k, 1, m) {
        for(auto x : L[k]) for(auto y : R[k])
            res = min(res, mat[k][x] + mat[x][y] + mat[y][k]);
        FOR(i, 1, m) FOR(j, 1, m)
            mat[i][j] = min(mat[i][j], mat[i][k] + mat[k][j]);
    }
    printf("%d\n", res);
}

int main() {
#ifndef OYK_JUDGE
    freopen("fence6.in", "r", stdin); freopen("fence6.out", "w", stdout);
#endif // OYK_JUDGE
    memset(mat, 0x3f, sizeof(mat));
    scanf("%d", &m);
    for(int i = 0, x, y, c, n1, n2; i < m; ++i) {
        scanf("%d%d%d%d", &x, &c, &n1, &n2);
        REP(j, n1) {
            scanf("%d", &y);
            mat[x][y] = c;
            L[x].push_back(y);
        }
        REP(j, n2) {
            scanf("%d", &y);
            mat[x][y] = c;
            R[x].push_back(y);
        }
    }
    solve();
}
