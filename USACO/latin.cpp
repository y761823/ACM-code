/*
ID: y7618231
PROG: latin
LANG: C++11
*/
#ifdef OYK_JUDGE
#define longformat "%I64d"
#else
#define longformat "%lld"
#endif // OYK_JUDGE

#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

typedef long long LL;
#define REP(i, n) for(int i = 0; i < n; ++i)
#define FOR(i, s, t) for(int i = s; i <= t; ++i)

int myhash[9][9];
bool col[9][9], row[9][15];
int mat[9][9];
int n;

void calc(int &a, int &b) {
    vector<bool> vis(n);
    a = 0, b = 1;
    for(int i = 0; i < n; ++i) if(!vis[i]) {
        vis[i] = true;
        int cnt = 1;
        for(int j = mat[1][i]; j != i; j = mat[1][j])
            cnt++, vis[j] = true;
        a++;
        b *= cnt;
    }
    assert(b < 15);
}

int dfs(int dep) {
    if(dep == n * (n - 1)) return 1;
    int r = dep / n, c = dep % n, res = 0, a = -1, b = -1;
    if(dep == 2 * n) {
        calc(a, b);
        if(myhash[a][b] != -1) return myhash[a][b];
    }
    if(c == 0) {
        res += dfs(dep + 1);
    } else
    for(int i = 0; i < n; ++i) if(!row[r][i] && !col[c][i]) {
        row[r][i] = col[c][i] = true;
        mat[r][c] = i;
        res += dfs(dep + 1);
        row[r][i] = col[c][i] = false;
    }
    if(dep == 2 * n) myhash[a][b] = res;
    return res;
}

LL fra[] = {1, 1, 2, 6, 24, 120, 720, 5040};

int main() {
#ifndef OYK_JUDGE
    freopen("latin.in", "r", stdin); freopen("latin.out", "w", stdout);
#endif // OYK_JUDGE
    scanf("%d", &n);
    for(int i = 0; i < n; ++i)
        row[i][i] = col[i][i] = true,
        mat[0][i] = mat[i][0] = i;
    memset(myhash, -1, sizeof(myhash));
    printf(longformat "\n", fra[n - 1] * dfs(n));
}
