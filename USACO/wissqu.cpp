/*
ID: y7618231
PROG: wissqu
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
#include <cmath>
#include <vector>
#include <string>
#include <tuple>
using namespace std;

typedef long long LL;
#define REP(i, n) for(int i = 0; i < n; ++i)
#define FOR(i, s, t) for(int i = s; i <= t; ++i)

char mat[6][6];
bool vis[6][6];
int rest[] = {3, 3, 3, 3, 3};

int fr[] = {-1, -1, -1, 0, 1, 1, 1, 0};
int fc[] = {-1, 0, 1, 1, 1, 0, -1, -1};

tuple<char, int, int> ans[16];
int anscnt;

void print() {
    if(++anscnt > 1) return ;
    for(int i = 0; i < 16; ++i)
        printf("%c %d %d\n", get<0>(ans[i]), get<1>(ans[i]), get<2>(ans[i]));
}

bool check(int r, int c, char type) {
    for(int i = 0; i < 8; ++i)
        if(mat[r + fr[i]][c + fc[i]] == type) return false;
    return mat[r][c] != type;
}

void dfs2(int dep) {
    if(dep == 16) return print();
    REP(c, 5) if(rest[c])
    FOR(i, 1, 4) FOR(j, 1, 4) if(!vis[i][j] && check(i, j, c + 'A')) {
        char tmp = mat[i][j];
        mat[i][j] = c + 'A';
        vis[i][j] = true;
        rest[c]--;

        if(!anscnt) ans[dep] = make_tuple(c + 'A', i, j);
        dfs2(dep + 1);

        rest[c]++;
        vis[i][j] = false;
        mat[i][j] = tmp;
    }
}

void dfs1() {
    int c = 3;
    FOR(i, 1, 4) FOR(j, 1, 4) if(!vis[i][j] && check(i, j, c + 'A')) {
        char tmp = mat[i][j];
        mat[i][j] = c + 'A';
        vis[i][j] = true;
        if(!anscnt) ans[0] = make_tuple(c + 'A', i, j);
        dfs2(1);
        vis[i][j] = false;
        mat[i][j] = tmp;
    }
}

int main() {
#ifndef OYK_JUDGE
    freopen("wissqu.in", "r", stdin); freopen("wissqu.out", "w", stdout);
#endif // OYK_JUDGE
    for(int i = 1; i <= 4; ++i) scanf("%s", &mat[i][1]);
    dfs1();
    printf("%d\n", anscnt);
}
