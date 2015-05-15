#include <bits/stdc++.h>
using namespace std;
#define FOR(i, n) for(int i = 0; i < n; ++i)

const int MAXN = 1010;
const int INF = 0x3f3f3f3f;

int mat[MAXN][MAXN];
int n, m;

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 0; i <= n + 1; ++i)
        for(int j = 0; j <= m + 1; ++j)
            (i == 0 || j == 0 || i > n || j > m) ? mat[i][j] = INF : scanf("%d", &mat[i][j]);

    for(int j = m; j > 0; --j)
        for(int i = n; i > 0; --i)
            mat[i][j] = min(min(mat[i][j], mat[i][j + 1]), min(mat[i + 1][j], mat[i - 1][j + 1]));

    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= m; ++j) printf("%d ", mat[i][j]);
        puts("");
    }
}
