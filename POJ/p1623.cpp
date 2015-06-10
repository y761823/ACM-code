#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
#define FOR(i, a, b) for(int i = a; i <= b; ++i)

const int MAXN = 128 + 1;

struct Node {
    int son[4], sz;
    int hash;
} p[MAXN * MAXN * 8];

char mat[MAXN][MAXN];
int ans1, ans2, n, m, pcnt;

void init() {
    ans1 = ans2 = pcnt = 0;
    memset(mat, 0, sizeof(mat));
}

int check(int x1, int y1, int x2, int y2) {
    char t = mat[x1][y1];
    FOR(i, x1, x2) FOR(j, y1, y2) if(t != mat[i][j]) return -1;
    return t == '1';
}

void dfs(int &r, int x1, int y1, int x2, int y2) {
    ++ans1;
    int res = check(x1, y1, x2, y2);
    int s_cnt = p[r = pcnt++].hash = 0;
    p[r].sz = 1;
    p[r].hash = res;
    if(res == -1) {
        int midX = (x1 + x2) >> 1, midY = (y1 + y2) >> 1, mid = ((x2 - x1) >> 1) + 1;
        FOR(i, 0, 1) FOR(j, 0, 1) {
            dfs(p[r].son[s_cnt], x1 + i * mid, y1 + j * mid, midX + i * mid, midY + j * mid);
            p[r].sz += p[p[r].son[s_cnt++]].sz;
        }
    }
}

bool same(int r1, int r2) {
    if(p[r1].sz != p[r2].sz || p[r1].hash != p[r2].hash) return false;
    if(p[r1].hash != -1) return true;
    for(int i = 0; i < 4; ++i) {
        if(!same(p[r1].son[i], p[r2].son[i])) return false;
    }
    return true;
}

bool exist(int r) {
    for(int i = 0; i < r; ++i)
        if(same(i, r)) return true;
    return false;
}

void solve(int r) {
    if(p[r].sz == 1) return ;
    if(exist(r)) {
        ans2 += p[r].sz;
    } else {
        for(int i = 0; i < 4; ++i) solve(p[r].son[i]);
    }
}

int expand(int x) {
    for(int i = 1; i <= 128; i <<= 1)
        if(x <= i) return i;
    return 128;
}

int main() {
    while(scanf("%d%d", &n, &m) != EOF) {
        if(n == 0 && m == 0) break;
        init();
        for(int i = 0; i < n; ++i) scanf("%s", mat[i]);
        n = expand(max(n, m));
        FOR(i, 0, n - 1) FOR(j, 0, n - 1)
            if(mat[i][j] == 0) mat[i][j] = '0';
        int root;
        dfs(root, 0, 0, n - 1, n - 1);
        solve(root);
        printf("%d %d\n", ans1, ans1 - ans2);
    }
}
