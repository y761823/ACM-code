#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

#define foreach(iter, v) for(__typeof(v.begin()) iter = v.begin(); iter != v.end(); ++iter)

const int MAXN = 33;

char mat[MAXN][MAXN];
int row[MAXN];
int n, m, ans;

void dfs(int r, int c, int bit) {
    if(r == n) {
        ans = min(ans, max(c, __builtin_popcount(bit)));
    } else {
        dfs(r + 1, c, bit | row[r]);
        dfs(r + 1, c + 1, bit);
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 0; i < n; ++i) {
        scanf("%s", mat[i]);
        for(int j = 0; j < m; ++j)
            if(mat[i][j] == '*') row[i] |= (1 << j);
    }

    ans = n;
    dfs(0, 0, 0);
    printf("%d\n", ans);
}
