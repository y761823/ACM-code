/*
ID: y7618231
PROG: snail
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
#include <unordered_map>
using namespace std;
typedef long long LL;
#define REP(i, n) for(int i = 0; i < n; ++i)
#define REPr(i, n) for(int i = n - 1; i >= 0; --i)
#define FOR(i, s, t) for(int i = s; i <= t; ++i)
#define FORr(i, s, t) for(int i = t; i >= s; --i)

const int MAXN = 123;
const int MOD = 1000000007;

int fr[] = {-1, 0, 1, 0};
int fc[] = {0, 1, 0, -1};

char mat[MAXN][MAXN];
int n, m, ans;

void dfs(int r, int c, int f, int cnt) {
    vector<pair<int, int>> list;
    int nr = r + fr[f], nc = c + fc[f];
    while(mat[nr][nc] == '.') {
        mat[r = nr][c = nc] = 'v';
        list.push_back(make_pair(r, c));
        nr = r + fr[f], nc = c + fc[f];
    }

    cnt += list.size();
    if(mat[nr][nc] == '#' && list.size()) {
        dfs(r, c, (f + 1) % 4, cnt);
        dfs(r, c, (f + 3) % 4, cnt);
    } else {
        ans = max(ans, cnt);
    }

    for(auto p : list) mat[p.first][p.second] = '.';
}

int main() {
#ifndef OYK_JUDGE
    freopen("snail.in", "r", stdin); freopen("snail.out", "w", stdout);
#endif // OYK_JUDGE
    scanf("%d%d", &n, &m);
    memset(mat, '#', sizeof(mat));
    FOR(i, 1, n) FOR(j, 1, n) mat[i][j] = '.';
    while(m--) {
        char c; int r;
        scanf(" %c%d", &c, &r);
        mat[r][c - 'A' + 1] = '#';
    }
    mat[1][1] = 'v';
    dfs(1, 1, 1, 1);
    dfs(1, 1, 2, 1);
    printf("%d\n", ans);
}
