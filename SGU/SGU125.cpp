#include <bits/stdc++.h>
using namespace std;
#define FOR(i, n) for(int i = 0; i < n; ++i)

const int MAXN = 5;

int b[MAXN][MAXN], a[MAXN][MAXN];
int n;

void maintain(int r1, int c1, int r2, int c2, int val) {
    if(a[r1][c1] < a[r2][c2]) b[r1][c1] -= val;
    if(a[r1][c1] > a[r2][c2]) b[r2][c2] -= val;
}

bool update(int r1, int c1, int r2, int c2) {
    maintain(r1, c1, r2, c2, 1);
    return b[r1][c1] >= 0 && b[r2][c2] >= 0;
}

void recover(int r1, int c1, int r2, int c2) {
    maintain(r1, c1, r2, c2, -1);
}

bool dfs(int dep) {
    if(dep == n * n) {
        return accumulate(b[n - 1], b[n - 1] + n, 0) == 0;
    }
    int r = dep / n, c = dep % n;
    for(a[r][c] = 1; a[r][c] <= 9; ++a[r][c]) {
        bool flag1 = (r == 0 || update(r, c, r - 1, c));
        bool flag2 = (c == 0 || update(r, c, r, c - 1));
        if(flag1 && flag2) if(r == 0 || b[r - 1][c] == 0) {
            if(dfs(dep + 1)) return true;
        }
        if(r > 0) recover(r, c, r - 1, c);
        if(c > 0) recover(r, c, r, c - 1);
    }
    return false;
}

bool solve() {
    if(!dfs(0)) return false;
    FOR(i, n) {
        FOR(j, n) printf("%d ", a[i][j]);
        puts("");
    }
    return true;
}

int main() {
    scanf("%d", &n);
    assert(n <= 3);
    FOR(i, n) FOR(j, n) scanf("%d", &b[i][j]);
    if(!solve()) puts("NO SOLUTION");
}
