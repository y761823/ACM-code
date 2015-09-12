#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <map>
using namespace std;
typedef long long LL;
#define REP(i, n) for(int i = 0; i < n; ++i)

const int MAXN = 12;
const char number[] = "1234";

char mat[MAXN][MAXN];
int pi[4], pj[4];
int n, L, w, h, tari, tarj;
int limit;

map<int, int> myhash;

void find_target(int &i, int &j, char tar) {
    for(i = 1; i <= h; ++i)
        for(j = 1; j <= w; ++j)
            if(mat[i][j] == tar) return ;
}

int encode() {
    int res = 0;
    for(int i = 0; i < n; ++i) {
        res = (res << 8) | (pi[i] << 4) | (pj[i]);
    }
    return res;
}

bool exist(int dep) {
    int t = encode();
    if(myhash[t] >= dep) return true;
    myhash[t] = dep;
    return false;
}

bool movef(int i, int j, int &ti, int &tj, int f) {
    static int fx[] = {0, 1, 0, -1};
    static int fy[] = {1, 0, -1, 0};
    ti = i; tj = j;
    while(mat[ti + fx[f]][tj + fy[f]] == '.')
        ti += fx[f], tj += fy[f];
    return ti != i || tj != j;
}

bool dfs(int dep) {
    if(dep == 0 || exist(dep)) return false;
    for(int v = 0; v < n; ++v) {
        int i = pi[v], j = pj[v], ti, tj;
        for(int f = 0; f < 4; ++f) if(movef(i, j, ti, tj, f)) {
            mat[i][j] = '.'; mat[ti][tj] = number[v]; pi[v] = ti; pj[v] = tj;
            if(v == 0 && ti == tari && tj == tarj) return true;
            if(dfs(dep - 1)) return true;
            mat[i][j] = number[v]; mat[ti][tj] = '.'; pi[v] =  i; pj[v] =  j;
        }
    }
    return false;
}

void solve() {
    find_target(tari, tarj, 'X');
    mat[tari][tarj] = '.';
    for(int i = 0; i < n; ++i)
        find_target(pi[i], pj[i], number[i]);
    for(limit = 1; limit <= L; ++limit) {
        myhash.clear();
        if(dfs(limit)) break;
    }
    if(limit <= L) printf("%d\n", limit);
    else puts("NO SOLUTION");
}

int main() {
    while(scanf("%d%d%d%d", &n, &w, &h, &L) != EOF) {
        memset(mat, 0, sizeof(mat));
        for(int i = 1; i <= h; ++i) scanf("%s", mat[i] + 1);
        solve();
    }
}
